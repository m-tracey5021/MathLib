#include "Algebra/equation.h"
#include "Algebra/equationComponents.h"
#include <ctype.h>
#include <string>
#include <utility>
#include <map>

using namespace std;

pair<int, int> parseCoefficient(string expStr, int startIndex);

pair<TermBase*, int> parseTerm(string expStr, int startIndex, bool currenSign);

pair<RationalExpression*, int> parseRational(string expStr, int startIndex, bool currentSign);

pair<RadicalExpression*, int> parseRadical(string expStr, int startIndex, bool currentSign);

pair<Polynomial*, int> parseExpression(string expStr, int startIndex, bool currentSign);

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

pair<int, int> parseCoefficient(string expStr, int startIndex){
    pair<int, int> coefficientTerminatingInfo;
    char currentChar = expStr[startIndex];
    string digitStr = "";
    while(isdigit(currentChar)){
        digitStr += currentChar;
        startIndex ++;
        currentChar = expStr[startIndex];
    }
    int coefficient = stoi(digitStr);
    coefficientTerminatingInfo.first = coefficient;
    coefficientTerminatingInfo.second = startIndex;
    return coefficientTerminatingInfo;
}

pair<TermBase*, int> parseTerm(string expStr, int startIndex, bool currentSign){
    pair<TermBase*, int> terminatingInfo;

    //CompoundTerm* currentTerm = new CompoundTerm();
    //currentTerm->setSign(currentSign);
    //currentTerm->setExponent(1);

    CompoundTerm* currentTerm = nullptr;

    bool termIncomplete = true;
    bool increment = true;
    int i = startIndex;

    while (termIncomplete){ // while loop to determine beginning and end of term

        

        char currentChar = expStr[i];

        if (currentChar == '\000'){
            terminatingInfo.first = currentTerm;
            terminatingInfo.second = i;
            return terminatingInfo;
        }else if (currentChar == '+' | 
                  currentChar == '-' |
                  currentChar == '/' | 
                  currentChar == '}' | 
                  currentChar == ')'){
            termIncomplete = false;
            increment = false;
        }else if (isalpha(currentChar)){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
            }
            AtomicTerm<char>* atom = new AtomicTerm<char>(currentSign, 1, currentChar);
            currentTerm->appendTerm(atom);
            increment = true;
            
        }else if (isdigit(currentChar)){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
            }
            pair<int, int> coeffcientTerminatingInfo = parseCoefficient(expStr, i);
            int coefficient = coeffcientTerminatingInfo.first;
            int terminatingPos = coeffcientTerminatingInfo.second;
            AtomicTerm<int>* atom = new AtomicTerm<int>(currentSign, 1, coefficient);
            currentTerm->appendTerm(atom);
            i = terminatingPos;
            increment = false;
        }else if (currentChar == '{'){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
            }
            pair<RationalExpression*, int> rationalTerminatingInfo = parseRational(expStr, i + 1, currentSign);
            RationalExpression* rational = rationalTerminatingInfo.first;
            int terminatingPos = rationalTerminatingInfo.second;
            currentTerm->appendTerm(rational);
            //currentTerm = rational;
            i = terminatingPos;
            increment = false;
        }else if (currentChar == '['){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
            }
            pair<RadicalExpression*, int> radicalTerminatingInfo = parseRadical(expStr, i + 1, currentSign);
            RadicalExpression* radical = radicalTerminatingInfo.first;
            int terminatingPos = radicalTerminatingInfo.second;
            currentTerm->appendTerm(radical);
            //currentTerm = radical;
            i = terminatingPos;
            increment = false;
        }else if (currentChar == '('){
            if (currentTerm == nullptr){
                currentTerm = new CompoundTerm();
            }
            pair<Polynomial*, int> polynomialTerminatingInfo = parseExpression(expStr, i + 1, currentSign);
            Polynomial* polynomial = polynomialTerminatingInfo.first;
            int terminatingPos = polynomialTerminatingInfo.second;
            currentTerm->appendTerm(polynomial);
            //currentTerm = polynomial;
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

    
    
    terminatingInfo.first = currentTerm;
    terminatingInfo.second = i;
    return terminatingInfo;
}

pair<RationalExpression*, int> parseRational(string expStr, int startIndex, bool currentSign){
    pair<RationalExpression*, int> terminatingInfo;
    RationalExpression* rational = new RationalExpression();

    TermBase* num;
    TermBase* denom;

    int numStartIndex = startIndex;
    int denumStartIndex;
    int terminatingPos;

    bool numSign = parseForSign(expStr, numStartIndex);
    if (!numSign){
        numStartIndex ++;
    }
    pair<TermBase*, int> numTerminatingInfo = parseTerm(expStr, numStartIndex, currentSign);
    num = numTerminatingInfo.first;
    denumStartIndex = numTerminatingInfo.second + 1; // + 1 to account for division symbol

    bool denomSign = parseForSign(expStr, denumStartIndex);
    if (!denomSign){
        denumStartIndex ++;
    }
    pair<TermBase*, int> denomTerminatingInfo = parseTerm(expStr, denumStartIndex, denomSign);
    denom = denomTerminatingInfo.first;
    terminatingPos = denomTerminatingInfo.second + 1;

    rational->setNum(num);
    rational->setDenom(denom);

    string termStr = rational->toString();

    terminatingInfo.first = rational;
    terminatingInfo.second = terminatingPos; // returns one past the end of the brackets
    return terminatingInfo;
    
}

pair<RadicalExpression*, int> parseRadical(string expStr, int startIndex, bool currentSign){
    pair<RadicalExpression*, int> radicalTerminatingInfo;
    RadicalExpression* radical = new RadicalExpression();





    return radicalTerminatingInfo;
}

pair<Polynomial*, int> parseExpression(string expStr, int startIndex, bool currentSign){
    pair<Polynomial*, int> polynomialTerminatingInfo;
    Polynomial* polynomial = new Polynomial();

    int polynomialTerminatingPos;
    bool polynomialIncomplete = true;

    while (polynomialIncomplete){ // first while loop to move onto next term
        
        TermBase* currentTerm = nullptr; 
        bool termSign = parseForSign(expStr, startIndex); // get the sign of the first term
        bool termIncomplete = true;
        int termTerminatingPos;
        char termTerminatingChar;

        while (termIncomplete){ // second while loop to move from term to term
            
            pair<TermBase*, int> terminatingInfo = parseTerm(expStr, startIndex, termSign);
            currentTerm = terminatingInfo.first;
            termTerminatingPos = terminatingInfo.second;
            termTerminatingChar = expStr[termTerminatingPos];
            startIndex = termTerminatingPos;

            // need to add term to polynomial only under certain conditions, like when 
            // the terminating char is '}' but it is not after another type of closing bracket          
            // im thinking make the parseTerm funtion return null if no term, and then appendTerm doesnt do anything

            polynomial->appendTerm(currentTerm);

            if (termTerminatingChar == '+'){
                termSign = true;
                termIncomplete = false;
                startIndex = termTerminatingPos + 1;
            }else if (termTerminatingChar == '-'){
                termSign = false;
                termIncomplete = false;
                startIndex = termTerminatingPos + 1;
            }else if (termTerminatingChar == ')'){ // polynomial is complete
                termSign = false;
                termIncomplete = false;
                polynomialIncomplete = false;
                polynomialTerminatingPos = termTerminatingPos + 1;
            }else if (termTerminatingChar == '('){

            }

            if (expStr[startIndex] == '\000'){ // if polynomial is top level and doesnt have brackets
                termIncomplete = false;
                polynomialIncomplete = false;
                polynomialTerminatingPos = startIndex;
            }
            
        }     
    }
    string termStr = polynomial->toString();
    Polynomial poly = *polynomial;

    polynomialTerminatingInfo.first = polynomial;
    polynomialTerminatingInfo.second = polynomialTerminatingPos; // returns one past the end of the brackets
    return polynomialTerminatingInfo;
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
