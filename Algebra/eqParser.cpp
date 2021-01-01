#include "equation.h"
#include "equationComponents.h"
#include <string>
#include <map>

using namespace std;

enum class ParseState {
    Default,
    AdditionParsed,
    NegativeParsed,
    SubtractionParsed,
    AtomicParsed,
    TermParsed,
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

void formTerm(bool currentSign, std::vector<TermBase*>& currentTerms, std::vector<TermBase*>& atomsToAdd){
    TermContainer* newTerm;
    if (atomsToAdd.size() == 1){
        atomsToAdd[0]->setSign(currentSign);
        currentTerms.push_back(atomsToAdd[0]);
    }else if (atomsToAdd.size() > 1){
        newTerm = new TermContainer(currentSign, nullptr, nullptr, OperationType::Multiplication, atomsToAdd);
        currentTerms.push_back(newTerm);
    }
}


TermBase* parseExpression(string expStr, bool expSign, int& i){ // starts iterating from INSIDE te brackets

    
    ParseState state = ParseState::Default;
    OperationType opType = OperationType::Multiplication;
    std::vector<TermBase*> currentTerms;

    //TermContainer* expression = new TermContainer();
    //expression->setOperationType(OperationType::Summation);

    

    bool currentSign = true; // = parseForSign(expStr, i); // get the sign of the first term in the expression

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
                opType = OperationType::Summation;
                termIncomplete = false;
                //currentSign = true;
            }else if (currentChar == '-'){   
                if (state == ParseState::Default){
                    state = ParseState::NegativeParsed;
                }else{
                    state = ParseState::SubtractionParsed;
                    opType = OperationType::Summation;
                    termIncomplete = false;
                }
                //currentSign = false;
            }else if (currentChar == '/' | 
                        currentChar == '|' | 
                        currentChar == '}' | 
                        currentChar == ']' | 
                        currentChar == ')' | 
                        currentChar == '\000'){
                    if (state == ParseState::AdditionParsed | state == ParseState::SubtractionParsed){
                        
                    }
                    state = ParseState::ExpressionParsed;
                    termIncomplete = false;
                    expressionIncomplete = false;
            }else if (isdigit(currentChar)){

                int coefficient = parseCoefficient(expStr, i);
                Constant* constant = new Constant(true, nullptr, nullptr, coefficient);
                currentAtoms.push_back(constant);
                previousTerm = constant;

                if (state == ParseState::Default | state == ParseState::NegativeParsed){
                    state = ParseState::AtomicParsed;
                }else if (state == ParseState::AtomicParsed){
                    state = ParseState::TermParsed;
                }



            }else if (isalpha(currentChar)){

                Variable* variable = new Variable(true, nullptr, nullptr, expStr[i]);
                currentAtoms.push_back(variable);
                previousTerm = variable;

                if (state == ParseState::Default | state == ParseState::NegativeParsed){
                    state = ParseState::AtomicParsed;
                }else if (state == ParseState::AtomicParsed){
                    state = ParseState::TermParsed;
                }

            }else if (currentChar == '^'){

                i ++;

                currentSign = parseForSign(expStr, i);

                if (currentSign){
                    i += 1;
                }else{
                    i += 2;
                }

                TermBase* exponent = parseExpression(expStr, currentSign, i);
                //exponent->setSign(currentSign);
                previousTerm->setExponent(exponent);
                priorIncrement = true;

            }else if (currentChar == '{'){

                TermContainer* rationalContainer = new TermContainer();
                rationalContainer->setOperationType(OperationType::Division);
                rationalContainer->setSign(currentSign);
                
                i ++;

                TermBase* num = parseExpression(expStr, currentSign, i);
                TermBase* denom = parseExpression(expStr, currentSign, i);    
                
                rationalContainer->appendTerm(num);
                rationalContainer->appendTerm(denom);
                currentTerms.push_back(rationalContainer);
                previousTerm = rationalContainer;
                priorIncrement = true;
  
            }else if (currentChar == '['){

                i ++;

                TermBase* root = parseExpression(expStr, currentSign, i);
                TermBase* radicalContainer = parseExpression(expStr, currentSign, i);
                radicalContainer->setRoot(root);
                radicalContainer->setSign(currentSign);
                currentTerms.push_back(radicalContainer);
                previousTerm = radicalContainer;
                priorIncrement = true;

            }else if (currentChar == '('){

                i ++;

                TermBase* subExpression = parseExpression(expStr, currentSign, i);
                currentTerms.push_back(subExpression);
                previousTerm = subExpression;
                priorIncrement = true;
                
            }
            
            if (!priorIncrement){
                i ++;
            }         
        } 

        // form a term from the currentAtoms vector here

        formTerm(currentSign, currentTerms, currentAtoms);

        if (state == ParseState::AdditionParsed){

            currentSign = true;
            opType = OperationType::Summation;

        }else if (state == ParseState::NegativeParsed){

            currentSign = false;
            
        }else if (state == ParseState::SubtractionParsed){

            currentSign = false;
            opType = OperationType::Summation;
            
        }else if (state == ParseState::AtomicParsed) {
        
        }else if (state == ParseState::TermParsed){
        
        }else if (state == ParseState::ExpressionParsed){

            if (currentTerms.size() == 0){
                return nullptr;
            }else if (currentTerms.size() == 1){
                return currentTerms[0];
            }else{
                return new TermContainer(expSign, nullptr, nullptr, opType, currentTerms);
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
