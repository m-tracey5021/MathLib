#include <cstring>
#include <string>
#include "Trees\treeElement.h"
#include "Trees\operatorType.h"
#include "Trees\staticOperand.h"
#include "Trees\variableOperand.h"
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


OperatorType getOperatorType(char value){
    if (value == '='){
        return OperatorType::Equals;
    }else if (value == '^'){
        return OperatorType::Exponent;
    }else if (value == '/'){
        return OperatorType::Division;
    }else if (value == '*'){
        return OperatorType::Multiplication;
    }else if (value == '+'){
        return OperatorType::Addition;
    }else if (value == '-'){
        return OperatorType::Subtraction;
    }else{
        throw "Char value does not correspond to operatorType";
    }
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

int* parseForMainOperator(char* eq, int start, int end){
    int largestWidth = -1;
    int pos = -1;
    bool parenthesised = 0;

    for (int i = start; i < end; i ++){
        if (charIsOperator(eq[i])){
            OperatorType type = getOperatorType(eq[i]);
            if (type == OperatorType::Equals){
                return new int[2]{i, 0};
            }else{
                int* brackets = findSurroundingBrackets(eq, i);
                int widthHere = brackets[1] - brackets[0];
                if (widthHere == 0){
                    largestWidth = 0;
                    pos = i;
                    parenthesised = 0;
                }

                if (widthHere > largestWidth & largestWidth != 0){
                    largestWidth = widthHere;
                    pos = i;
                    parenthesised = 1;
                }
            } 
        }
    }
    return new int[2]{pos, parenthesised};
}

int parseForFirstInt(char* eq, int start, int end){
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
            return convertedInt;
        }
    }
    return -1;
}

char parseForFirstChar(char* eq, int start, int end){
    for (int i = start; i < end; i ++){
        if (isalpha(eq[i])){
            return eq[i];
        }
    }
    return '0';
}

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






