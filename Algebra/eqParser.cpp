#include "equation.h"
#include "equationComponents.h"
#include <string>
#include <map>

#define LB '('
#define RB ')'

using namespace std;

enum class ParseState {
    Default,
    AdditionParsed,
    SubtractionParsed,
    MultiplicationParsed,
    AtomicParsed,
    TermParsed,
    ExpressionParsed,
    NegativeSubExpressionParsed
};

enum class ParseCondition {
    CharTermination,
    TermTermination,
    ExpressionTermination
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

void formTerm(bool currentSign, std::vector<TermBase*>& toSum, std::vector<TermBase*>& toMultiply){
    TermContainer* newTerm;
    if (toMultiply.size() == 1){
        toMultiply[0]->setSign(currentSign);
        toSum.push_back(toMultiply[0]);
    }else if (toMultiply.size() > 1){
        newTerm = new TermContainer(currentSign, nullptr, nullptr, OperationType::Multiplication, toMultiply);
        toSum.push_back(newTerm);
    }
}

void setParseState(ParseState& state,  ParseCondition condition){
    if (condition == ParseCondition::CharTermination){
        if (state == ParseState::Default){
            state = ParseState::AtomicParsed;
        }else if (state == ParseState::AtomicParsed | 
                    state == ParseState::TermParsed | 
                    state == ParseState::ExpressionParsed){
            state = ParseState::TermParsed;
        }
    }else if (condition == ParseCondition::TermTermination){
        if (state == ParseState::Default){
            state = ParseState::TermParsed;
        }else if (state == ParseState::AtomicParsed | 
                    state == ParseState::TermParsed | 
                    state == ParseState::ExpressionParsed){
            state = ParseState::TermParsed;
        }
    }else if (condition == ParseCondition::ExpressionTermination){
        if (state == ParseState::AdditionParsed |
            state == ParseState::SubtractionParsed){
                state = ParseState::ExpressionParsed;
        }
    }
}


TermBase* parseExpression(string expStr, ParseState state, int& i){ // starts iterating from INSIDE te brackets

    
    //ParseState state = ParseState::Default;
    //OperationType opType = OperationType::Multiplication;
    std::vector<TermBase*> toSum;

    //TermContainer* expression = new TermContainer();
    //expression->setOperationType(OperationType::Summation);

    
    
    bool currentSign = true; // = parseForSign(expStr, i); // get the sign of the first term in the expression
    bool parentSign;
    state == ParseState::NegativeSubExpressionParsed ? parentSign = false : parentSign = true;

    state = ParseState::Default;

    bool expressionIncomplete = true;

    while (expressionIncomplete){ // first while loop to gauge completion of summed expression

        
        bool termIncomplete = true;
        bool priorIncrement;
        char currentChar;

        // TermContainer* currentTerm = nullptr; // init pointers
        std::vector<TermBase*> toMultiply;
        TermBase* previousTerm = nullptr;

        while (termIncomplete){ // second while loop to move from term to term

            priorIncrement = false;

            currentChar = expStr[i];

            if (currentChar == '+'){
                state = ParseState::AdditionParsed;
                //opType = OperationType::Summation;
                termIncomplete = false;
                //currentSign = true;
            }else if (currentChar == '-'){   
                if (state == ParseState::Default){
                    currentSign = false;
                }else{
                    state = ParseState::SubtractionParsed;
                    //opType = OperationType::Summation;
                    termIncomplete = false;
                }
                //currentSign = false;
            }else if (currentChar == '/' | 
                        currentChar == '|' | 
                        currentChar == '}' | 
                        currentChar == ']' | 
                        currentChar == ')' | 
                        currentChar == '\000'){
                    setParseState(state, ParseCondition::ExpressionTermination);
                    termIncomplete = false;
                    expressionIncomplete = false;
            }else if (isdigit(currentChar)){

                int coefficient = parseCoefficient(expStr, i);
                Constant* constant = new Constant(true, nullptr, nullptr, coefficient);
                toMultiply.push_back(constant);
                previousTerm = constant;

                setParseState(state, ParseCondition::CharTermination);

            }else if (isalpha(currentChar)){

                Variable* variable = new Variable(true, nullptr, nullptr, expStr[i]);
                toMultiply.push_back(variable);
                previousTerm = variable;

                setParseState(state, ParseCondition::CharTermination);

            }else if (currentChar == '^'){

                i ++;

                currentSign = parseForSign(expStr, i);

                if (currentSign){
                    i += 1;
                }else{
                    i += 2;
                }

                ParseState subState;
                currentSign ? subState = ParseState::Default : subState = ParseState::NegativeSubExpressionParsed;

                TermBase* exponent = parseExpression(expStr, subState, i);
                //exponent->setSign(currentSign);
                previousTerm->setExponent(exponent);
                priorIncrement = true;

            }else if (currentChar == '{'){

                TermContainer* rationalContainer = new TermContainer();
                rationalContainer->setOperationType(OperationType::Division);
                rationalContainer->setSign(currentSign);
                
                i ++;

                TermBase* num = parseExpression(expStr, ParseState::Default, i);
                TermBase* denom = parseExpression(expStr, ParseState::Default, i);    
                
                rationalContainer->appendTerm(num);
                rationalContainer->appendTerm(denom);
                toMultiply.push_back(rationalContainer);

                setParseState(state, ParseCondition::TermTermination);
                previousTerm = rationalContainer;
                priorIncrement = true;
  
            }else if (currentChar == '['){

                i ++;

                ParseState subState;
                currentSign ? subState = ParseState::Default : subState = ParseState::NegativeSubExpressionParsed;

                TermBase* root = parseExpression(expStr, ParseState::Default, i);
                TermBase* radicalContainer = parseExpression(expStr, subState, i);
                radicalContainer->setRoot(root);
                //radicalContainer->setSign(currentSign);
                toMultiply.push_back(radicalContainer);

                setParseState(state, ParseCondition::TermTermination);
                previousTerm = radicalContainer;
                priorIncrement = true;

            }else if (currentChar == '('){

                i ++;

                ParseState subState;
                currentSign ? subState = ParseState::Default : subState = ParseState::NegativeSubExpressionParsed;

                TermBase* subExpression = parseExpression(expStr, subState, i);
                toMultiply.push_back(subExpression);

                setParseState(state, ParseCondition::TermTermination);
                previousTerm = subExpression;
                priorIncrement = true;
                
            }
            
            if (!priorIncrement){
                i ++;
            }         
        } 

        // form a term from the currentAtoms vector here

        formTerm(currentSign, toSum, toMultiply);

        if (toSum.size() == 0){
            return nullptr;
        }

        if (state == ParseState::AdditionParsed){

            currentSign = true;
            //opType = OperationType::Summation;

        }else if (state == ParseState::SubtractionParsed){

            currentSign = false;
            //opType = OperationType::Summation;
            
        }else if (state == ParseState::AtomicParsed | state == ParseState::TermParsed) {

            return toSum[0];

        }else if (state == ParseState::ExpressionParsed){

            return new TermContainer(parentSign, nullptr, nullptr, OperationType::Summation, toSum);
            
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
    return parseExpression(expStr, ParseState::Default, startIndex);
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
