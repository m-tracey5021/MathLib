#include "eqTree.h"

bool EqTree::charIsOperator(char c){
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

int* EqTree::findSurroundingBrackets(string eq, int startPos){
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
            if (i != eq.length()){
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

int* EqTree::parseForMainOperator(string eq, int start, int end){
    int largestWidth = -1;
    int pos = -1;
    bool parenthesised = 0;

    for (int i = start; i < end; i ++){
        if (charIsOperator(eq[i])){
            char op = eq[i];
            if (op == '='){
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

vector<string> EqTree::parseForOperands(string eq){
    vector<string> operands;
    for (int i = 0; i < eq.length(); i ++){
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
            string sub = eq.substr(i, j - i);
            operands.push_back(sub);
            i = j + 1;
        }else if (isalpha(eq[i])){
            string sub = "";
            sub.push_back(eq[i]);
            operands.push_back(sub);
        }
    }
    return operands;
}

/*

void EqTree::assignEquation(string eq){
    int* (*operatorParsePointer)(string, int, int);
    operatorParsePointer = parseForMainOperator;
    rootNode->traverse(operatorParsePointer);
}

*/