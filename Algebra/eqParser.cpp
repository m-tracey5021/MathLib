#include "equation.h"
#include "equationComponents.h"
#include <string>
#include <map>

using namespace std;

enum class ParseState {
    AdditionParsed,
    SubtractionParsed,
    ExpressionParsed,
};

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

void initMultiplicativeTerms(TermContainer*& current){ //}, TermContainer*& previous){
    if (current == nullptr){
        current = new TermContainer();
        current->setOperationType(OperationType::Multiplication);
        //previous = current;
    }
    
}

TermBase* formTerm(bool currentSign, std::vector<TermBase*> atoms){
    if (atoms.size() == 1){
        atoms[0]->setSign(currentSign);
        return atoms[0];
    }else if (atoms.size() > 1){
        TermContainer* newTerm = new TermContainer();
        newTerm->setOperationType(OperationType::Multiplication);
        newTerm->setSign(currentSign);
        newTerm->setTerms(atoms);
        return newTerm;
    }else{
        return nullptr;
    }
}



TermBase* parseExpression(string expStr, bool expSign, int& i){ // starts iterating from INSIDE te brackets

    
    ParseState state;
    std::vector<TermBase*> currentTerms;

    //TermContainer* expression = new TermContainer();
    //expression->setOperationType(OperationType::Summation);

    

    bool currentSign = parseForSign(expStr, i); // get the sign of the first term in the expression

    bool expressionIncomplete = true;

    while (expressionIncomplete){ // first while loop to gauge completion of summed expression

        
        bool termIncomplete = true;
        bool priorIncrement;
        char currentChar;

        // TermContainer* currentTerm = nullptr; // init pointers
        std::vector<TermBase*> currentAtoms;
        TermBase* previousTerm = nullptr;

        while (termIncomplete){ // second while loop to move from term to term

            priorIncrement = false;

            currentChar = expStr[i];

            if (currentChar == '+'){
                state = ParseState::AdditionParsed;
                termIncomplete = false;
                //currentSign = true;
            }else if (currentChar == '-'){   
                state = ParseState::SubtractionParsed;
                termIncomplete = false;
                //currentSign = false;
            }else if (currentChar == '/' | 
                        currentChar == '|' | 
                        currentChar == '}' | 
                        currentChar == ']' | 
                        currentChar == ')' | 
                        currentChar == '\000'){
                    state = ParseState::ExpressionParsed;
                    termIncomplete = false;
                    expressionIncomplete = false;
            }else if (isdigit(currentChar)){
                //initMultiplicativeTerms(currentTerm);

                int coefficient = parseCoefficient(expStr, i);
                Constant* constant = new Constant(true, nullptr, nullptr, coefficient);
                //currentTerm->appendTerm(constant);
                currentAtoms.push_back(constant);
                previousTerm = constant;





            }else if (isalpha(currentChar)){
                //initMultiplicativeTerms(currentTerm);

                Variable* variable = new Variable(true, nullptr, nullptr, expStr[i]);
                //currentTerm->appendTerm(variable);
                currentAtoms.push_back(variable);
                previousTerm = variable;

            }else if (currentChar == '^'){

                i ++;

                currentSign = parseForSign(expStr, i);

                if (currentSign){
                    i += 1;
                }else{
                    i += 2;
                }

                TermBase* exponent = parseExpression(expStr, currentSign, i);
                exponent->setSign(currentSign);
                previousTerm->setExponent(exponent);
                priorIncrement = true;

            }else if (currentChar == '{'){
                //initMultiplicativeTerms(currentTerm);

                TermContainer* rationalContainer = new TermContainer();
                rationalContainer->setOperationType(OperationType::Division);
                rationalContainer->setSign(currentSign);
                
                i ++;

                TermBase* num = parseExpression(expStr, currentSign, i);
                TermBase* denom = parseExpression(expStr, currentSign, i);    
                
                rationalContainer->appendTerm(num);
                rationalContainer->appendTerm(denom);
                currentTerms.push_back(rationalContainer);
                //currentTerm->appendTerm(rationalContainer);
                previousTerm = rationalContainer;
                priorIncrement = true;
  
            }else if (currentChar == '['){
                //initMultiplicativeTerms(currentTerm);

                i ++;

                TermBase* root = parseExpression(expStr, currentSign, i);
                TermBase* radicalContainer = parseExpression(expStr, currentSign, i);
                radicalContainer->setRoot(root);
                radicalContainer->setSign(currentSign);
                currentTerms.push_back(radicalContainer);
                //currentTerm->appendTerm(radicalContainer);
                previousTerm = radicalContainer;
                priorIncrement = true;

            }else if (currentChar == '('){
                //initMultiplicativeTerms(currentTerm);

                i ++;

                TermBase* subExpression = parseExpression(expStr, currentSign, i);
                currentTerms.push_back(subExpression);
                //currentTerm->appendTerm(subExpression);
                previousTerm = subExpression;
                priorIncrement = true;
                
            }
            
            if (!priorIncrement){
                i ++;
            }         
        } 

        // form a term from the currentAtoms vector here

        TermBase* newTerm;

        if (state == ParseState::AdditionParsed){

            newTerm = formTerm(currentSign, currentAtoms);
            currentTerms.push_back(newTerm);
            currentSign = true;

        }else if (state == ParseState::SubtractionParsed){

            newTerm = formTerm(currentSign, currentAtoms);
            currentTerms.push_back(newTerm);
            currentSign = false;
            
        }else if (state == ParseState::ExpressionParsed){

            newTerm = formTerm(currentSign, currentAtoms);

            if (newTerm != nullptr){
                currentTerms.push_back(newTerm);
            }

            if (currentTerms.size() == 0){
                return nullptr;
            }else if (currentTerms.size() == 1){
                return currentTerms[0];
            }else{
                return new TermContainer(expSign, nullptr, nullptr, OperationType::Summation, currentTerms);
            }
            
        }else{
            return nullptr; // or throw error more likely
        }

        /*
        if (currentTerm != nullptr){
            expression->appendTerm(currentTerm);
        }
        */
          
    }

    //return expression;
}

TermBase* parseExpression(string expStr){
    bool expSign = true;
    int startIndex = 0;
    return parseExpression(expStr, expSign, startIndex);
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
