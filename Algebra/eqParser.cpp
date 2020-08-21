#include "equation.h"
#include "equationComponents.h"
#include <ctype.h>
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


Term* parseTerm(string termStr){
    Term* prevTerm = nullptr;
    ComplexTerm* complex = new ComplexTerm();

    for (int i = 0; i < termStr.length(); i ++){
        char currentChar = termStr[i];
        if (isalpha(currentChar)){
            AtomicTerm<char>* atom = new AtomicTerm(1, 1, currentChar);
            complex->appendTerm(*atom);
            prevTerm = atom;
        }else if (isdigit(currentChar)){
            int i = (int)currentChar;
            AtomicTerm<int>* atom = new AtomicTerm(1, 1, i);
            complex->appendTerm(*atom);
            prevTerm = atom;
        }else if (currentChar = '{'){
            int* brackets = findSurroundingBrackets(termStr, i, '{');
            string exponentStr = termStr.substr(brackets[0], brackets[1] - brackets[0]);
            int exponent = stoi(exponentStr);
            prevTerm->setExponent(exponent);
        }else{
            // throw error
        }
    }
    return complex;
}

Expression* parseExpression(string expStr){
    /*
        1: initialise pointers 
            1a: initialise expression
            1b: inititalise pointer to previous term for the purpose of adding exponential information
            1c: initialise current sign
        2: iterate through the string
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
                       once the expression value has been returned, add it to the previous term to continue a complex term


    */

    // initialise pointers

    Expression* expression = new Expression();
    Term* prevTerm = nullptr;
    bool currentSign = 1;

    // iterate through string

    for (int i = 0; i < expStr.length(); i ++){
        char currentChar = expStr[i];

        // create atoms

        if (currentChar == '+'){
            currentSign = 1;
        }else if (currentChar == '-'){
            currentSign = 0;
        }else if (currentChar == '^'){
            // get following exponent and add to prevTerm
        }else if (isalpha(currentChar)){
            AtomicTerm<char>* atom = new AtomicTerm(currentSign, 1, currentChar);
            prevTerm = atom;
        }else if (isdigit(currentChar)){
            int i = (int)currentChar;
            AtomicTerm<int>* atom = new AtomicTerm(currentSign, 1, i);
            prevTerm = atom;
        }else if (currentChar == '('){
            // find brackets and recurse
            int* brackets = findSurroundingBrackets(expStr, i, '(');
        }else if (currentChar == '['){
            // find root, brackets and recurse
        }else if (currentChar == ')' | currentChar == ']'){
            // pass
        }else{
            // throw error
        }

        // commence search for the continuation of a complex term

        ComplexTerm* complexTerm = nullptr;
        bool complex = false;
        bool cont = true;
        int j = i + 1;

        while (cont){
            char nextChar = expStr[j];
            if (nextChar == '+'){
                expression->appendTerm(*prevTerm); // appends the atom to the expression because a complex term was not found
                currentSign = 1;
                cont = false;
            }else if (nextChar == '-'){ 
                expression->appendTerm(*prevTerm); // appends the atom to the expression because a complex term was not found
                currentSign = 0;
                cont = false;
            }else if (nextChar == '/'){
            
            }else if (nextChar == '^'){
                // get following exponent and add to prevTerm, continue loop
                
            }else if (isalpha(nextChar)){
                AtomicTerm<char>* atom = new AtomicTerm(currentSign, 1, nextChar);
                complexTerm->appendTerm(*atom);
                prevTerm = complexTerm;
                complex = true;
            }else if (isdigit(nextChar)){
                int i = (int)nextChar;
                AtomicTerm<int>* atom = new AtomicTerm(currentSign, 1, i);
                complexTerm->appendTerm(*atom);
                prevTerm = complexTerm;
                complex = true;
            }else if (nextChar == '('){
                // find brackets and recurse
                int* brackets = findSurroundingBrackets(expStr, j, '(');
                string subExpStr = expStr.substr(brackets[0], brackets[1] - brackets[0]);
                Term* subExp = parseExpression(subExpStr);
                complexTerm->appendTerm(*subExp);
                prevTerm = complexTerm;
                complex = true;
            }else if (nextChar == '['){
                // find root, brackets and recurse
            }else if (nextChar == ')' | nextChar == ']'){
                // pass
            }else{
                // throw error
            }
            j ++;
        }
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
