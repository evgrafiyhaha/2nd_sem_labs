#include "logic.h"

void doTranslate(AppContext* context, char * inputValue, int inNumberSystem, int outNumberSystem) {
    char  numbers[] = "0123456789abcdef";
    int errorCode = errorChecker(numbers,inputValue,inNumberSystem);
    context->errorData = errorCode;
    if (errorCode == Error_Code_0) {
        switch(inNumberSystem) {
        case 2:
            fromBinary(context,numbers,inputValue,outNumberSystem);
            break;
        case 10:
            fromDecimal(context,numbers,inputValue,outNumberSystem);
            break;
        default:
            fromOtherSys(context,numbers,inputValue,inNumberSystem,outNumberSystem);

        }
    } else {
        context->currentValue = DEFAULT_VALUE;
    }
}

void fromDecimal(AppContext* context, char* numbers, char * inputValue, int outNumberSystem) {
    int sign = signCheck10(inputValue);

    switch(outNumberSystem) {
    case 2:

        if (sign) {
            char * translatedTo2 = translateToOther(inputValue,numbers,outNumberSystem);
            context->currentValue = translatedTo2;
        } else {
            char * twosComplement = toTwosComplement(inputValue);
            char * translatedTo2 = translateToOther(twosComplement,numbers,outNumberSystem);
            context->currentValue = translatedTo2;
            free(twosComplement);
        }
        break;
    case 10:
        context->currentValue = inputValue;
        break;
    default:
        if (sign) {
            char * translatedToOther = translateToOther(inputValue,numbers,outNumberSystem);
            context->currentValue = translatedToOther;
        } else {
            char * twosComplement = toTwosComplement(inputValue);
            char * translatedToOther = translateToOther(twosComplement,numbers,outNumberSystem);
            context->currentValue = translatedToOther;
            free(twosComplement);
        }

    }
}

void fromBinary(AppContext* context, char* numbers, char * inputValue, int outNumberSystem) {
    int sign = signCheck2(inputValue);
    switch(outNumberSystem) {
    case 2:
        context->currentValue = inputValue;
        break;
    case 10:
        if (sign) {
            char * translatedTo10 = translateTo10(inputValue,numbers,2);
            context->currentValue = translatedTo10;
        } else {
            char * translatedTo10 = translateTo10(inputValue,numbers,2);
            char * directCode = toDirectCode(translatedTo10);
            context->currentValue = directCode;
            free(translatedTo10);
        }
        break;
    default:
        char * translatedTo10 = translateTo10(inputValue,numbers,2);
        char * translatedToOther = translateToOther(translatedTo10,numbers,outNumberSystem);
        context->currentValue = translatedToOther;
        free(translatedTo10);
    }
}

void fromOtherSys(AppContext* context, char* numbers, char * inputValue, int inNumberSystem, int outNumberSystem) {
    char * translatedTo10 = translateTo10(inputValue,numbers,inNumberSystem);
    int sign = signCheck10(translatedTo10);
    free(translatedTo10);
    switch(outNumberSystem) {
    case 2:
    {
        char * translatedTo10 = translateTo10(inputValue,numbers,inNumberSystem);
        char * translatedTo2 = translateToOther(translatedTo10,numbers,2);
        context->currentValue = translatedTo2;
        free(translatedTo10);
        break;
    }
    case 10:
        if (sign) {
            char * translatedTo10 = translateTo10(inputValue,numbers,inNumberSystem);
            context->currentValue = translatedTo10;
        } else {
            char * translatedTo10 = translateTo10(inputValue,numbers,inNumberSystem);
            char * directCode = toDirectCode(translatedTo10);
            context->currentValue = directCode;
            free(translatedTo10);
        }
        break;
    default:
        char * translatedTo10 = translateTo10(inputValue,numbers,inNumberSystem);
        char * translatedToOther = translateToOther(translatedTo10,numbers,outNumberSystem);
        context->currentValue = translatedToOther;
        free(translatedTo10);
    }
}


void initialize(AppContext* context) {
    context->currentValue = DEFAULT_VALUE;
    context->errorData = Error_Code_0;
}

void doSwitch(AppContext* context, char* inputValue, int inNumberSystem, int outNumberSystem) {
    char  numbers[] = "0123456789abcdef";
    int errorCode = errorChecker(numbers,inputValue,inNumberSystem);
    context->errorData = errorCode;
    if (errorCode == Error_Code_0) {
        char* tempValue = context->currentValue;
        context->currentValue = inputValue;
        context->inputValue = tempValue;
        context->inNumberSystem = outNumberSystem;
        context->outNumberSystem = inNumberSystem;
    }
}


int errorChecker(char* numbers,char* inputValue,int inNumberSystem) {
    int errorCode = Error_Code_0;
    if (checkForValidSigns(numbers,inputValue,inNumberSystem) == 0 && checkForBitLimit(numbers,inputValue,inNumberSystem) == 0) {
        errorCode = Error_Code_1;
    } else if (checkForBitLimit(numbers,inputValue,inNumberSystem) == 0) {
        errorCode = Error_Code_2;
    } else if (checkForValidSigns(numbers,inputValue,inNumberSystem) == 0) {
        errorCode = Error_Code_3;
    }
    return errorCode;
}

int checkForValidSigns(char* numbers,char* inputValue,int inNumberSystem) {
    int validationSuccessfull = 1;
    for (unsigned i = 0;i < strlen(inputValue);i++) {
        if (!((findIndexInNumbers(inputValue[i],numbers) < inNumberSystem && findIndexInNumbers(inputValue[i],numbers) != -1))){
            if (inNumberSystem == 10 && i == 0 && inputValue[i] == '-') {
                ;
            } else {
                validationSuccessfull = 0;
            }

        }
    }
    return validationSuccessfull;
}

int checkForBitLimit(char* numbers,char* inputValue,int inNumberSystem) {
    int validationSuccessfull = 1;
    if (inNumberSystem == 2 && strlen(inputValue) > LENGTH_CONSTANT) {
        validationSuccessfull = 0;
    } else if (inNumberSystem == 10) {
        char* translatedTo2 = translateToOther(inputValue,numbers,2);
        if (strlen(translatedTo2) > LENGTH_CONSTANT) {
            validationSuccessfull =0;
        }
        free(translatedTo2);
    } else {
        char* translatedTo10 = translateTo10(inputValue,numbers,inNumberSystem);
        char* translatedTo2 = translateToOther(translatedTo10,numbers,2);
        if (strlen(translatedTo2) > LENGTH_CONSTANT) {
            validationSuccessfull = 0;
        }
        free(translatedTo10);
        free(translatedTo2);
    }
    return validationSuccessfull;
}

char* translateTo10(char* input, char* numbers,int system) {
    int len = strlen(input);
    int temp;
    char tempChar;
    long long intResult = 0;
    char* result = (char*)malloc(MEMORY_CONSTANT);
    for (int i = len-1;i >= 0;i--) {
        tempChar = input[len-i-1];
        temp = findIndexInNumbers(tempChar,numbers);
        intResult += temp * pow(system,i);
    }
    result = longLongToString(intResult);
    return result;
}

char * translateToOther(char* input, char* numbers, int system) {
    unsigned intValue;
    unsigned temp;
    char tempChar;
    int counter = 0;
    char* result = (char*)malloc(MEMORY_CONSTANT);
    intValue = stringToUnsigned(input);
    while (intValue > 0) {
        temp = intValue % system;
        tempChar = numbers[temp];
        intValue /= system;
        result[counter] = tempChar;
        counter++;
    }
    rotate(result);
    return result;
}

char* toTwosComplement(char* input) {
    char* buffer = (char*)malloc(MEMORY_CONSTANT);
    unsigned num = stringToUnsigned(input);
    if (buffer != NULL) {
        buffer = unsignedTostring(num);
    }
    return buffer;
}

char * toDirectCode(char* input) {
    char* buffer = (char*)malloc(MEMORY_CONSTANT);
    int num = stringToInt(input);
    if (buffer != NULL) {
        buffer = intTostring(num);
    }
    return buffer;
}


char* unsignedTostring(unsigned input) {
    char* buffer = (char*)malloc(MEMORY_CONSTANT);
    if (buffer != NULL) {
        snprintf(buffer, MEMORY_CONSTANT, "%u", input);
    }
    return buffer;
}

unsigned stringToUnsigned(char* string){
    int intStr = atoi(string);
    unsigned ui = intStr;
    return ui;
}

int stringToInt(char* string){
    return atoi(string);
}

long long stringToLongLong(char* string) {
    return atoll(string);
}

char * intTostring(int input) {
    char* buffer = (char*)malloc(MEMORY_CONSTANT);
    if (buffer != NULL) {
        snprintf(buffer, MEMORY_CONSTANT, "%d", input);
    }
    return buffer;
}

char* longLongToString(long long value) {
    char* buffer = (char*)malloc(MEMORY_CONSTANT);
    if (buffer != NULL) {
        snprintf(buffer, MEMORY_CONSTANT, "%lld", value);
    }
    return buffer;
}

void rotate(char* str) {
    int length = strlen(str);
    int i;
    char temp;
    for (i = 0; i < length / 2; i++) {
        temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

int findIndexInNumbers(char  input, char* numbers) {
    for (unsigned i = 0;i < strlen(numbers);i++) {
        if (input == numbers[i]) {
            return i;
        }
    }
    return -1;
}

int signCheck10(char* input) {
    int isPositive = 1;
    if (*input == '-') {
        isPositive = 0;
    }
    return isPositive;
}

int signCheck2(char* input){
    int isPositive = 1;
    if (strlen(input) == LENGTH_CONSTANT && *input == '1') {
        isPositive = 0;
    }
    return isPositive;
}
