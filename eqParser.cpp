#include "Algebra/equation.h"
#include "Algebra/equationComponents.h"
#include <ctype.h>
#include <string>
#include <utility>
#include <map>

using namespace std;

Polynomial* parsePolynomial(string expStr);

int* findSurroundingBrackets(string eq, int startPos, char bracketType){
    char bracketTypeOpen;
    char bracketTypeClosed;

    if (bracketType = '('){
        bracketTypeOpen = '(';
        bracketTypeClosed = ')';
    }else if (bracketType = '['){
        bracketTypeOpen = '[';
        bracketTypeClosed = ']';
    }else if (bracketType == '{'){
        bracketTypeOpen = '{';
        bracketTypeClosed = '}';
    }else {
        // throw error
    }

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
        if (currentChar == bracketTypeClosed){
            numberOfOpeningBrackets --;
        }else if (currentChar == bracketTypeOpen){
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
        if (currentChar == bracketTypeClosed){
            numberOfClosingBrackets ++;
        }else if (currentChar == bracketTypeOpen){
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

bool parseForSign(string expStr, int index){
    if (expStr[index] == '-'){
        return true;
    }else{
        return false;
    }
}

pair<TermBase*, int> parseTerm(string expStr, int startIndex, bool currentSign){
    pair<TermBase*, int> terminatingInfo;
    
    TermBase* currentTerm;
    CompoundTerm* compound = new CompoundTerm();
    
    currentTerm = compound;
    currentTerm->setSign(currentSign);

    bool termIncomplete = true;
    int i = startIndex;

    while (termIncomplete){ // second while loop to move from term to term

        if (i > expStr.length()){
            terminatingInfo.first = currentTerm;
            terminatingInfo.second = i;
            return terminatingInfo;
        }

        char currentChar = expStr[i];

        if (currentChar == '+' | 
            currentChar == '-' |  
            currentChar == ')'){
            termIncomplete = false;
        }else if (isalpha(currentChar)){
            AtomicTerm<char>* atom = new AtomicTerm<char>(currentSign, 1, currentChar);
            currentTerm->appendTerm(*atom);
        }else if (isdigit(currentChar)){
            int i = (int)currentChar;
            AtomicTerm<int>* atom = new AtomicTerm<int>(currentSign, 1, i);
            currentTerm->appendTerm(*atom);
        }else if (currentChar == '/'){
            RationalExpression* rational = new RationalExpression();
            
            char nextChar = expStr[i + 1];
            bool denomSign;
            if (nextChar == '-'){
                denomSign = false;
                nextChar = expStr[i + 2];
            }else{
                denomSign = true;
            }

            pair<TermBase*, int> denomTerminatingInfo = parseTerm(expStr, i + 2, denomSign);
            rational->setNum(currentTerm);
            rational->setDenom(denomTerminatingInfo.first);
            currentTerm = rational;
        }else if (currentChar == '('){
            int* brackets = findSurroundingBrackets(expStr, i, '(');
            string subExpStr = expStr.substr(brackets[0], brackets[1] - brackets[0]);
            Polynomial* subExp = parsePolynomial(subExpStr);
            currentTerm->appendTerm(*subExp);
        }
        i ++;
    }
    
    terminatingInfo.first = currentTerm;
    terminatingInfo.second = i;
    return terminatingInfo;
}

Polynomial* parsePolynomial(string expStr){

    Polynomial* polynomial = new Polynomial();
    bool currentSign = parseForSign(expStr, 0);

    int startIndex = 0;
    int terminatingPos;
    char terminatingChar;

    bool polynomialIncomplete = true;

    while (polynomialIncomplete){ // first while loop to move onto next term
        
        TermBase* currentTerm = nullptr; // all of the below can be assigned to this pointer for the purpose of combining terms
        bool termIncomplete = true;

        while (termIncomplete){ // second while loop to move from term to term
            
            pair<TermBase*, int> terminatingInfo = parseTerm(expStr, startIndex, currentSign);
            currentTerm = terminatingInfo.first;
            terminatingPos = terminatingInfo.second;
            terminatingChar = expStr[terminatingPos];

            polynomial->appendTerm(*currentTerm);

            if (terminatingChar == '+'){
                currentSign = true;
                termIncomplete = false;
                startIndex = terminatingPos + 1;
            }else if (terminatingChar == '-'){
                currentSign = false;
                termIncomplete = false;
                startIndex = terminatingPos + 1;
            }else if (terminatingChar == ')'){
                termIncomplete = false;
                startIndex = terminatingPos + 1;
            }
        }
        if (startIndex > expStr.length()){
            polynomialIncomplete = false;
        }
    }
}

Equation* parseEquation(string eqStr){
    /*
    1: initialise pointers 
        1a: initialise two expressions and pointer to current expression to build 
        1b: inititalise pointer to previous term for the purpose of adding exponential information
        1c: initialise current sign
    2: iterate through string
    3: at current char, check whether preceded by a ^

        4: if true - add exponent to previous term
        5: if false - create new atomic term with value of char
            5a: set previous term to newly created atomic term

    6: enter while loop - iterate over characters afer previous term until an operator or a bracket is reached
        6a: check character that has been read
            6ai: on - +, -, / break loop and complete creation of the term, set previous term to newly created complex term
                 and add term to current expression with sign
            6aii: on ^ enter block that adds exponent to term but does not break loop
            6aiii: on (, ), [root] do not break loop but find brackets and recurse into expression within via stringToExpression


    */
}
