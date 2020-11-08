#include "equation.h"
#include "equationComponents.h"
//#include <ctype.h>
#include <string>

using namespace std;

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

bool parseForSign(string expStr, int i){
    if (expStr[i] == '-'){
        return false;
    }else if (expStr[i] == '+'){
        return true;
    }else{
        return true;
    }
}

int parseCoefficient(string expStr, int& i){
    char currentChar = expStr[i];
    string digitStr = "";
    while(isdigit(currentChar)){
        digitStr += currentChar;
        i ++;
        currentChar = expStr[i];
    }
    int coefficient = stoi(digitStr);
    i --;

    return coefficient;
}

void initMultiplicativeTerms(TermContainer*& current, TermContainer*& previous){
    if (current == nullptr){
        current = new TermContainer();
        current->setOperationType(OperationType::Multiplication);
        previous = current;
    }
    
}

TermContainer* parseExpression(string expStr, int& i){ // starts iterating from INSIDE te brackets
    TermContainer* expression = new TermContainer();
    expression->setOperationType(OperationType::Summation);

    bool expressionIncomplete = true;

    while (expressionIncomplete){ // first while loop to gauge completion of summed expression

        bool currentSign = parseForSign(expStr, i); // get the sign of the first term in the expression
        bool termIncomplete = true;
        bool priorIncrement;
        char currentChar;

        TermContainer* currentTerm = nullptr; // init pointers
        TermContainer* previousTerm = nullptr;

        while (termIncomplete){ // second while loop to move from term to term

            priorIncrement = false;

            currentChar = expStr[i];

            if (currentChar == '+'){
                termIncomplete = false;
                currentSign = true;
            }else if (currentChar == '-'){   
                termIncomplete = false;
                currentSign = false;
            }else if (currentChar == '/' | 
                        currentChar == '|' | 
                        currentChar == '}' | 
                        currentChar == ']' | 
                        currentChar == ')' | 
                        currentChar == '\000'){
                    termIncomplete = false;
                    expressionIncomplete = false;
            }else if (isdigit(currentChar)){
                initMultiplicativeTerms(currentTerm, previousTerm);

                int coefficient = parseCoefficient(expStr, i);
                Constant* constant = new Constant(currentSign, nullptr, nullptr, coefficient);
                currentTerm->setCoefficient(constant);
                //currentTerm->appendTerm(constant);

            }else if (isalpha(currentChar)){
                initMultiplicativeTerms(currentTerm, previousTerm);

                Variable* variable = new Variable(currentSign, nullptr, nullptr, expStr[i]);
                currentTerm->appendTerm(variable);

            }else if (currentChar == '^'){

                i ++;

                currentSign = parseForSign(expStr, i);

                if (currentSign){
                    i += 1;
                }else{
                    i += 2;
                }

                TermContainer* exponent = parseExpression(expStr, i);
                exponent->setSign(currentSign);
                previousTerm->setExponent(exponent);
                priorIncrement = true;

            }else if (currentChar == '{'){
                initMultiplicativeTerms(currentTerm, previousTerm);

                TermContainer* rationalContainer = new TermContainer();
                rationalContainer->setOperationType(OperationType::Division);
                rationalContainer->setSign(currentSign);
                
                i ++;

                TermContainer* num = parseExpression(expStr, i);
                TermContainer* denom = parseExpression(expStr, i);    
                
                rationalContainer->appendTerm(num);
                rationalContainer->appendTerm(denom);
                currentTerm->appendTerm(rationalContainer);
                priorIncrement = true;
  
            }else if (currentChar == '['){
                initMultiplicativeTerms(currentTerm, previousTerm);

                i ++;

                TermContainer* root = parseExpression(expStr, i);
                TermContainer* radicalContainer = parseExpression(expStr, i);
                radicalContainer->setRoot(root);
                radicalContainer->setSign(currentSign);
                currentTerm->appendTerm(radicalContainer);
                priorIncrement = true;

            }else if (currentChar == '('){
                initMultiplicativeTerms(currentTerm, previousTerm);

                i ++;

                TermContainer* subExpression = parseExpression(expStr, i);
                currentTerm->appendTerm(subExpression);
                priorIncrement = true;
                
            }
            
            if (!priorIncrement){
                i ++;
            }         
        } 

        expression->appendTerm(currentTerm);  
    }

    return expression;
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
