//DTMF.h

#ifndef DTMF_H
#define DTMF_H
#include <math.h>
#include<iostream>
#include <cstdlib>

#define PI 3.14159
typedef struct KeypadTone
{
	const char *sign;
	int highFrequency;
	int lowFrequency;
}KeypadTone;
static KeypadTone keypadTone[16] = {
		{"1", 1209, 697},
		{"2", 1336, 697},
		{"3", 1477, 697},
		{"A", 1633, 697},
		{"4", 1209, 770},
		{"5", 1336, 770},
		{"6", 1477, 770},
		{"B", 1633, 770},
		{"7", 1209, 852},
		{"8", 1336, 852},
		{"9", 1477, 852},
		{"C", 1633, 852},
		{"*", 1209, 941},
		{"0", 1336, 941},
		{"#", 1477, 941},
		{"D", 1633, 941}
	};
class DTMF
{
	
	private:
		void CalcSignalDFT(float *signalInputArray,float *signalReArray,float *signalImArray,int signalLength);
	public:
		DTMF();
		~DTMF();
		void DTMF_Generator(char keypadInput,int signalLength,int rate,float *dataOutput);
		char* DTMF_Detector(float *dtmfSignal,int signalLength,int rate);
};		





#endif

