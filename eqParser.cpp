#include "Algebra/equation.h"
#include "Algebra/equationComponents.h"
#include <ctype.h>
#include <string>
#include <utility>
#include <map>

using namespace std;

int parseCoefficient(string expStr, int& startIndex);

pair<TermBase*, int> parseTerm(string expStr, int startIndex, bool currenSign);

TermBase* parseExpression(string expStr, int startIndex, bool currentSign);

Equation* parseEquation(string eqStr);

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
        return false;
    }else if (expStr[index] == '+'){
        return true;
    }else  {
        return true;
    }
}

int parseCoefficient(string expStr, int& startIndex){
    char currentChar = expStr[startIndex];
    string digitStr = "";
    while(isdigit(currentChar)){
        digitStr += currentChar;
        startIndex ++;
        currentChar = expStr[startIndex];
    }
    int coefficient = stoi(digitStr);
    startIndex --;

    return coefficient;
}

pair<TermBase*, int> parseExponent(string expStr, int startIndex, bool currentSign){
    pair<Expression*, int> exponentTerminatingInfo = parseExpression(expStr, startIndex, currentSign);
    Expression* exponent = exponentTerminatingInfo.first;
    int exponentTerminatingPos = exponentTerminatingInfo.second;


}

pair<TermBase*, int> parseTerm(string expStr, int startIndex, bool currentSign){
    pair<TermBase*, int> terminatingInfo;

    //CompoundTerm* currentTerm = new CompoundTerm();
    //currentTerm->setSign(currentSign);
    //currentTerm->setExponent(1);

    CompoundTerm* currentTerm = nullptr;
    TermBase* previousTerm = nullptr;

    bool termIncomplete = true;
    bool increment = true;
    bool exponentParsed = false;
    int i = startIndex;

    while (termIncomplete){ // while loop to determine beginning and end of term

        

        char currentChar = expStr[i];

        if (currentChar == '\000'){
            if (exponentParsed){
                terminatingInfo.first = previousTerm;
            }else{
                terminatingInfo.first = currentTerm;
            }
            terminatingInfo.second = i;
            return terminatingInfo;
        }else if (currentChar == '+' | 
                  currentChar == '-' |
                  currentChar == '/' | 
                  currentChar == '}' |
                  currentChar == ']' |  
                  currentChar == ')'){
            termIncomplete = false;
            increment = false;
        }else if (isalpha(currentChar)){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
                previousTerm = currentTerm;
            }
            AtomicTerm<char>* atom = new AtomicTerm<char>(currentSign, nullptr, currentChar);
            currentTerm->appendTerm(atom);
            if (currentTerm->getCoefficient() == nullptr){
                currentTerm->setCoefficient(new AtomicTerm<int>(1, nullptr, 1));
            }
            increment = true;
            
        }else if (isdigit(currentChar)){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
                previousTerm = currentTerm;
            }
            pair<int, int> coeffcientTerminatingInfo = parseCoefficient(expStr, i);
            int coefficient = coeffcientTerminatingInfo.first;
            int terminatingPos = coeffcientTerminatingInfo.second;
            AtomicTerm<int>* atom = new AtomicTerm<int>(currentSign, nullptr, coefficient);
            //currentTerm->appendTerm(atom);
            currentTerm->setCoefficient(atom);
            i = terminatingPos;
            increment = false;
        }else if (currentChar == '^'){
            pair<Expression*, int> exponentTerminatingInfo = parseExpression(expStr, i + 1, currentSign);
            Expression* exponent = exponentTerminatingInfo.first;
            int terminatingPos = exponentTerminatingInfo.second;
            previousTerm->setExponent(exponent);
            i = terminatingPos;
            exponentParsed = true;
            increment = true;
        }else if (currentChar == '{'){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
                previousTerm = currentTerm;
            }
            pair<RationalExpression*, int> rationalTerminatingInfo = parseRational(expStr, i + 1, currentSign);
            RationalExpression* rational = rationalTerminatingInfo.first;
            int terminatingPos = rationalTerminatingInfo.second;
            currentTerm->appendTerm(rational);
            if (currentTerm->getCoefficient() == nullptr){
                currentTerm->setCoefficient(new AtomicTerm<int>());
            }
            previousTerm = rational;
            i = terminatingPos;
            increment = false;
        }else if (currentChar == '['){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
                previousTerm = currentTerm;
            }
            pair<RadicalExpression*, int> radicalTerminatingInfo = parseRadical(expStr, i + 1, currentSign);
            RadicalExpression* radical = radicalTerminatingInfo.first;
            int terminatingPos = radicalTerminatingInfo.second;
            currentTerm->appendTerm(radical);
            previousTerm = radical;
            i = terminatingPos;
            increment = false;
        }else if (currentChar == '('){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
                previousTerm = currentTerm;
            }
            pair<Expression*, int> expressionTerminatingInfo = parseExpression(expStr, i + 1, currentSign);
            Expression* expression = expressionTerminatingInfo.first;
            int terminatingPos = expressionTerminatingInfo.second;
            currentTerm->appendTerm(expression);
            previousTerm = expression;
            i = terminatingPos;
            increment = false;
        }

        // just for debugging
        string termStr;
        if (currentTerm != nullptr){
            termStr = currentTerm->toString();
        }
        
        if (increment){
            i ++;
        }
    }

    
    if (exponentParsed){
        terminatingInfo.first = previousTerm;
    }else{
        terminatingInfo.first = currentTerm;
    }
    
    terminatingInfo.second = i;
    return terminatingInfo;
}



TermBase* parseExpression(string expStr, int startIndex, bool currentSign){
    TermContainer* expression = new TermContainer();
    expression->setOperationType(OperationType::Summation);

    int i = startIndex;
    bool expressionIncomplete = true;

    while (expressionIncomplete){ // first while loop to move onto next term
        
        TermContainer* currentTerm = nullptr;
        currentTerm->setOperationType(OperationType::Multiplication); 

        TermContainer* previousTerm = nullptr;

        bool termSign = parseForSign(expStr, startIndex); // get the sign of the first term
        bool termIncomplete = true;

        int globalCoefficient = 0;

        while (termIncomplete){ // second while loop to move from term to term



            char currentChar = expStr[i];

            if (currentChar == '\000'){
                return expression;
            }else if (currentChar == '+' | 
                    currentChar == '-' |
                    currentChar == '/' | 
                    currentChar == '}' |
                    currentChar == ']' |  
                    currentChar == ')'){
                termIncomplete = false;
            }else if (isalpha(currentChar)){
                if (currentTerm == nullptr){
                    currentTerm = new TermContainer();
                    previousTerm = currentTerm;
                }
                Variable* variable = new Variable(currentSign, 1, nullptr, expStr[i]);
                currentTerm->appendTerm(variable);
                if (globalCoefficient == 0){
                    currentTerm->setCoefficient(globalCoefficient);
                }
                
            }else if (isdigit(currentChar)){
                if (currentTerm == nullptr){
                    currentTerm = new TermContainer();
                    previousTerm = currentTerm;
                }
                globalCoefficient = parseCoefficient(expStr, i);
            }else if (currentChar == '^'){
                pair<Expression*, int> exponentTerminatingInfo = parseExpression(expStr, i + 1, currentSign);
                Expression* exponent = exponentTerminatingInfo.first;
                int terminatingPos = exponentTerminatingInfo.second;
                previousTerm->setExponent(exponent);
                i = terminatingPos;
                exponentParsed = true;
                increment = true;
            }else if (currentChar == '{'){
                if (currentTerm == nullptr){
                    currentTerm = new CompoundTerm();
                    previousTerm = currentTerm;
                }
                pair<RationalExpression*, int> rationalTerminatingInfo = parseRational(expStr, i + 1, currentSign);
                RationalExpression* rational = rationalTerminatingInfo.first;
                int terminatingPos = rationalTerminatingInfo.second;
                currentTerm->appendTerm(rational);
                if (currentTerm->getCoefficient() == nullptr){
                    currentTerm->setCoefficient(new AtomicTerm<int>());
                }
                previousTerm = rational;
                i = terminatingPos;
                increment = false;
            }else if (currentChar == '['){
                if (currentTerm == nullptr){
                    currentTerm = new CompoundTerm();
                    previousTerm = currentTerm;
                }
                pair<RadicalExpression*, int> radicalTerminatingInfo = parseRadical(expStr, i + 1, currentSign);
                RadicalExpression* radical = radicalTerminatingInfo.first;
                int terminatingPos = radicalTerminatingInfo.second;
                currentTerm->appendTerm(radical);
                previousTerm = radical;
                i = terminatingPos;
                increment = false;
            }else if (currentChar == '('){
                if (currentTerm == nullptr){
                    currentTerm = new CompoundTerm();
                    previousTerm = currentTerm;
                }
                pair<Expression*, int> expressionTerminatingInfo = parseExpression(expStr, i + 1, currentSign);
                Expression* expression = expressionTerminatingInfo.first;
                int terminatingPos = expressionTerminatingInfo.second;
                currentTerm->appendTerm(expression);
                previousTerm = expression;
                i = terminatingPos;
                increment = false;
            }





            
            pair<TermBase*, int> terminatingInfo = parseTerm(expStr, startIndex, termSign);
            currentTerm = terminatingInfo.first;
            termTerminatingPos = terminatingInfo.second;
            termTerminatingChar = expStr[termTerminatingPos];
            startIndex = termTerminatingPos;

            // need to add term to polynomial only under certain conditions, like when 
            // the terminating char is '}' but it is not after another type of closing bracket          
            // im thinking make the parseTerm funtion return null if no term, and then appendTerm doesnt do anything

            expression->appendTerm(currentTerm);

            if (termTerminatingChar == '+'){
                termSign = true;
                termIncomplete = false;
                startIndex = termTerminatingPos + 1;
            }else if (termTerminatingChar == '-'){
                termSign = false;
                termIncomplete = false;
                startIndex = termTerminatingPos + 1;
            }else if (termTerminatingChar == '/' | termTerminatingChar == '}' | termTerminatingChar == ']' | termTerminatingChar == ')'){ // polynomial is complete
                termSign = false;
                termIncomplete = false;
                expressionIncomplete = false;
                expressionTerminatingPos = termTerminatingPos + 1;
            }else if (termTerminatingChar == '\000'){ // if polynomial is top level and doesnt have brackets
                termIncomplete = false;
                expressionIncomplete = false;
                expressionTerminatingPos = startIndex;
            }
            
        }     
    }

    expressionTerminatingInfo.first = expression;
    expressionTerminatingInfo.second = expressionTerminatingPos; // returns one past the end of the brackets
    return expressionTerminatingInfo;
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
