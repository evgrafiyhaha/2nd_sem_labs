#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>

#define DEFAULT_VALUE ""
#define MEMORY_CONSTANT 64
#define LENGTH_CONSTANT 32

void doTranslate(AppContext* context, char * inputValue, int inNumberSystem, int outNumberSystem);
void initialize(AppContext* context);
void doSwitch(AppContext* context, char * inputValue, int inNumberSystem, int outNumberSystem);

int errorChecker(char* numbers, char* inputValue,int inNumberSystem);
int checkForValidSigns(char* numbers, char* inputValue, int inNumberSystem);
int checkForBitLimit(char* numbers, char* inputValue, int inNumberSystem);

enum ErroeCode {
    Error_Code_0,
    Error_Code_1,
    Error_Code_2,
    Error_Code_3
};


void fromDecimal(AppContext* context, char* numbers, char * inputValue, int outNumberSystem);
void fromBinary(AppContext* context, char* numbers, char * inputValue, int outNumberSystem);
void fromOtherSys(AppContext* context, char* numbers, char * inputValue, int inNumberSystem, int outNumberSystem);

char * translateTo10(char * input, char * numbers, int system);
char * translateToOther(char * input, char * numbers, int system);

char* toTwosComplement(char * input);
char * toDirectCode(char* input);

int findIndexInNumbers(char  input, char * numbers);
int signCheck10(char * input);
int signCheck2(char * input);
int stringToInt(char* string);
char * intTostring(int input);
long long stringToLongLong(char* string);
char* longLongToString(long long value);
unsigned stringToUnsigned(char* string);
char * unsignedTostring(unsigned input);
void rotate(char * str);

#endif // LOGIC_H
