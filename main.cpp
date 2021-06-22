//main.cpp
/*
功能：DTMF訊號產生及檢測
開發人員：李昶諺
日期：2021/06/21
*/
#include "DTMF.h"
#define RATE 		8000
#define SIGNAL_SIZE 512

using namespace std;
int main()
{
	DTMF dtmf;
	char keypad;
	char fileName[10];
	float OutData[RATE];
	int counter;
	while(true)
	{
	
		cout << "Please enter keypad sign：";
		cin >> keypad;
		sprintf(fileName,"K-%s.dat",&keypad);
		
		FILE *file = fopen(fileName,"w");
		dtmf.DTMF_Generator(keypad,SIGNAL_SIZE,RATE,OutData);
		for(counter = 0;counter < SIGNAL_SIZE;counter++)
			fprintf(file, "%f\n",OutData[counter]);
		cout << "DTMF signal generation completed!!" << endl;
		cout << "Data file name：" << fileName << endl << endl;
		cout << "Execute DTMF detection....." << endl;
		cout << "Detection result：" <<dtmf.DTMF_Detector(OutData,SIGNAL_SIZE,RATE) << endl;
	}


	system("pause");
	return 0;
}
