//DTMF.cpp

#include "DTMF.h"
using namespace std;


DTMF::DTMF()
{

}
DTMF::~DTMF()
{

}
void DTMF::CalcSignalDFT(float *signalInputArray,float *signalReArray,float *signalImArray,int signalLength)
{
	int index1,index2,index3;
	for(index1 = 0;index1 < signalLength;index1++)
	{
		signalReArray[index1] = 0;
		signalImArray[index1] = 0;
	}
	 
	//³z¹L³Å¥ß¸­Âà´«±N¿é¤J°T¸¹(®É°ì)Âà¦¨¹ê³¡©Mµê³¡(ÀW°ì)
	for(index2 = 0;index2 < (signalLength/2);index2++)
	{
		for(index3 = 0;index3 < signalLength;index3++)
		{
			signalReArray[index2] += signalInputArray[index3]*cos((2*PI*index2*index3)/signalLength);//¹ê³¡ƒ¨
			signalImArray[index2] -= signalInputArray[index3]*sin((2*PI*index2*index3)/signalLength);//µê³¡›éƒ¨ 
		}
	}
}
void DTMF::DTMF_Generator(char keypadInput,int signalLength,int rate,float *dataOutput)
{
	int index;
	float hFreq;
	float lFreq;
	
	//§PÂ_¿é¤J«öÁä©Ò¹ïÀ³ªº°ªÀW¤Î§CÀW »
	for(index = 0;index < 16;index++)
	{
		if(keypadInput == *keypadTone[index].sign)
		{
			hFreq = keypadTone[index].highFrequency;
			lFreq = keypadTone[index].lowFrequency;
			//cout << hFreq << "," << lFreq << endl;
		}
	}

	//Generator DTMF Signal
	for(index = 0;index < signalLength;index++)
	{
		//°ªÀW¥[§CÀW
		dataOutput[index] = 0.5*sinf((2*PI*hFreq*index)/rate); 
		dataOutput[index] += (0.5*sinf((2*PI*lFreq*index)/rate));
	}
}
char* DTMF::DTMF_Detector(float *dtmfSignal,int signalLength,int rate)
{
	float arrayReSignal[rate];
	float arrayImSignal[rate];
	float detectionSignal[8];
	int freqPositon[8];
	FILE *reFile,*imFile;
	
	reFile = fopen("ReData.dat","w");
	imFile = fopen("ImData.dat","w");
	
	//³]©w«öÁä¹ïÀ³ªºÀW²v¸ÑªR«×(ÀW²v*°T¸¹ªø«×/±Ä¼ËÀW²v)
	freqPositon[0] = (697*signalLength)/rate;
	freqPositon[1] = (770*signalLength)/rate;
	freqPositon[2] = (852*signalLength)/rate;
	freqPositon[3] = (941*signalLength)/rate;
	freqPositon[4] = (1209*signalLength)/rate;
	freqPositon[5] = (1336*signalLength)/rate;
	freqPositon[6] = (1477*signalLength)/rate;
	freqPositon[7] = (1633*signalLength)/rate;

	//¶i¦æÂ÷´²³Å¥ß¸­Âà´«¡A¿é¥X¹ê³¡¤Îµê³¡
	CalcSignalDFT(dtmfSignal,arrayReSignal,arrayImSignal,signalLength);
	
	int index;
	for(index = 0;index < signalLength;index++)
	{
		fprintf(reFile,"%f\n",arrayReSignal[index]);
		fprintf(imFile,"%f\n",arrayImSignal[index]);
	}
	
	int row = 0,column = 0;

	for(index = 0;index < 8;index++)
	{
		//¨úµ´¹ï­È(¹ê³¡¥­¤è¥[µê³¡¥­¤è¦A¶}®Ú¸¹)
		detectionSignal[index] = 
			sqrt(arrayReSignal[freqPositon[index]]*arrayReSignal[freqPositon[index]] 
			+ arrayImSignal[freqPositon[index]]*arrayImSignal[freqPositon[index]]);
		//cout << detectionSignal[index]  << endl;
	}
	float tempMaxValue = 0;
	//§ä§CÀW³Ì¤j¯à¶q¦ì¸m
	for(index = 0;index < 4  ;index++)
	{
		if(detectionSignal[index] > tempMaxValue)
			if(detectionSignal[index] > 0.0005)
			{	
				tempMaxValue = detectionSignal[index];
				row = index;
			}
	}
	tempMaxValue = 0;
	//§ä°ªÀW³Ì¤j¯à¶q¦ì¸m
	for(index = 4;index < 8;index++)
	{
		if(detectionSignal[index] > tempMaxValue)
			if(detectionSignal[index] > 0.0005)
			{
				tempMaxValue = detectionSignal[index];
				column = index;	
			}
	}
	//¨Ì°ª§CÀW¯à¶q³Ì¤j¦ì¸m§ä¥X©Ò«öªº«öÁä‰éµ
	if(row == 0) //697Hz
	{
		if(column == 4)	//1209Hz
			return "1";
		else if(column == 5) //1336Hz
			return "2";
		else if(column == 6) //1477Hz
			return "3";
		else if(column == 7) //1633Hz
			return "A";
	}
	else if(row == 1) //770Hz
	{
		if(column == 4)
			return "4";
		else if(column == 5)
			return "5";
		else if(column == 6)
			return "6";
		else if(column == 7)
			return "B";
	}
	else if(row == 2) //852Hz
	{
		if(column == 4)
			return "7";
		else if(column == 5)
			return "8";
		else if(column == 6)
			return "9";
		else if(column == 7)
			return "C";
	}
	else if(row == 3) //852Hz	
	{
		if(column == 4)
			return "*";
		else if(column == 5)
			return "0";
		else if(column == 6)
			return "#";
		else if(column == 7)
			return "D";
	}
}
