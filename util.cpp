#include <cstring>
#include <string>
#include "basicArithmeticFunctions.h"

using namespace std;

int stringLength(std::string str){
    int i = 0;
    while(str[i]){
        i ++;
    }
    return i;
}

bool stringIsEqual(std::string str1, std::string str2){
    bool isEqual = true;
    int length1 = stringLength(str1);
    int length2 = stringLength(str2);
    if (length1 != length2){
        return false;
    }else{
        for (int i = 0; i < length1; i ++){
            if (str1[i] != str2[i]){
                return false;
            }
        }
    }
    return true;
}

bool charIsNumeric(char c){
    if (c == '0' | 
            c == '1' | 
            c == '2' | 
            c == '3' | 
            c == '4' | 
            c == '5' | 
            c == '6' | 
            c == '7' | 
            c == '8' | 
            c == '9'){
        return true;
    }else{
        return false;
    }
}

bool charIsOperator(char c){
    if (c == '=' | 
            c == '^' | 
            c == '/' | 
            c == '*' | 
            c == '+' | 
            c == '-'){
        return true;
    }else{
        return false;
    }
}

char* substring(char* str, int startPos, int len){
    char* sub = new char[len];
    int posInNew = 0;
    for(int i = startPos; i < startPos + len; i ++){
        sub[posInNew] = str[i]; 
        posInNew ++;
    }
    return sub;
}

int convertToInt(char* numberStr, int len){
    int total = 0;
    for (int i = 0; i < len; i ++){
        int toAdd = numberStr[i] - '0';
        toAdd *= power(10, len - i - 1);
        total += toAdd;
    }
    return total;
}

int convertToInt(char* numberStr, int startIndex, int endIndex){
    int total = 0;
    for (int i = startIndex; i < endIndex; i ++){
        int toAdd = numberStr[i] - '0';
        toAdd *= power(10, endIndex - startIndex - i - 1);
        total += toAdd;
    }
    return total;
}

int* findSurroundingBrackets(char* eq, int startPos){
    int closingPos = -1;
    int openingPos = -1;
    bool closingFound = false;
    bool openingFound = false;
    int i = startPos;
    int j = startPos;
    int numberOfOpeningBrackets = 0;
    int numberOfClosingBrackets = 0;
    char currentChar;

    while (closingFound == false){
        currentChar = eq[i];
        if (currentChar == ')'){
            numberOfOpeningBrackets --;
        }else if (currentChar == '('){
            numberOfOpeningBrackets ++;
        }

        if (numberOfOpeningBrackets == -1){
            closingFound = true;
            closingPos = i;
        }else{
            if (i != strlen(eq)){
                i ++;
            }else{
                closingFound = true;
            }
        }  
    }

    while (openingFound == false){
        currentChar = eq[j];
        if (currentChar == ')'){
            numberOfClosingBrackets ++;
        }else if (currentChar == '('){
            numberOfClosingBrackets --;
        }

        if (numberOfClosingBrackets == -1){
            openingFound = true;
            openingPos = j;
        }else{
            if (j != 0){
                j --;
            }else{
                openingFound = true;
            }
        }
    }

    return new int[2]{openingPos, closingPos};

}

char parseForFirstChar(char* eq, int start, int end){
    for (int i = start; i < end; i ++){
        if (isalpha(eq[i])){
            return eq[i];
        }
    }
    return '0';
}

/*
TreeElement* parseForFirstOperand(char* eq, int start, int end){
    for (int i = start; i < end; i ++){
        if (isdigit(eq[i])){
            bool lastChar = false;
            int j = i + 1;
            while(lastChar == false){
                if (isdigit(eq[j])){
                    j ++;
                }else{
                    lastChar = true;
                }
            }
            char* sub = substring(eq, i, j - i);
            int convertedInt = convertToInt(sub, j - i);
            return new StaticOperand(convertedInt, "operand");
        }else if (isalpha(eq[i])){
            return new VariableOperand(eq[i], "operand");
        }
    }
    return nullptr;
}
*/






