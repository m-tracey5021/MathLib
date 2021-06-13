#include "mParser.h"
#include <typeinfo>

// #define RB ')'
// #define LB '('
// #define ADD '+'
// #define SUBTRACT '-'
// #define MULTIPLY '*'
// #define DIVIDE '/'
// #define RATIONAL_BEGIN '{'
// #define ROOT_START '['
// #define EXPONENT_BEGIN '^'
// #define FUNCTION_BEGIN 'f'
// #define ESCAPE_CHARACTER '|'

// The characters above will be special characters, not forming a string in keeping with these
// special characters will mean that the string is not well formed and the function will return
// an error.

// BNF Grammar using an extended definition where * denotes repition (0 - infinity), and
// ? denotes binary inclusion, and / denotes set subtraction

// ===================

// Expression ::= ?Root (Term | '(' Expression ')') *(('+' | '-') (Term | '(' Expression ')')) ?Exponent

// Term ::= Multiplication | Division | Constant | Variable

// Multiplication ::= ?Root (Constant *Variable) ?Exponent

// Division ::= ?Root (Term '/' Term) ?Exponent

// Root ::= '[' Expression ']v' 

// Exponent ::= '^{' Expression '}'

// Constant ::= *('1' - '9') *('0' - '9')

// Variable ::= ('a' - 'z') / ('v')

// ===================


// enum class ParseState{

// };

bool isOpeningBracket(char bracket){
    if (bracket == '(' ||
        bracket == '{' || 
        bracket == '['){
        return true;
    }else{
        return false;
    }
}

bool isClosingBracket(char bracket){
    if (bracket == ')' ||
        bracket == '}' || 
        bracket == ']'){
        return true;
    }else{
        return false;
    }
}

int findMatchingBracket(int i, string expression){

    char opening;
    char closing;

    if (expression[i] == '(' || expression[i] == ')'){
        opening = '(';
        closing = ')';
    }else if (expression[i] == '{' || expression[i] == '}'){
        opening = '{';
        closing = '}';
    }else if (expression[i] == '[' || expression[i] == ']'){
        opening = '[';
        closing = ']';
    }else{
        // throw error
    }

    int bracketStack = 0;
    if (expression[i] == opening){
        for (int j = i + 1; j < expression.size(); j ++){
            if (expression[j] == closing){
                bracketStack ++;
            }else if (expression[j] == opening){
                bracketStack --;
            }
            if (bracketStack == 1){
                int rootOperator = findMatchingBracket(j, expression) + 1;
                // j = scopeAuxOp(rootOperator, expression).end;
                return j;
            }
        }
    }else if (expression[i] == closing){
        for (int j = i - 1; j >= 0; j --){
            if (expression[j] == closing){
                bracketStack --;
            }else if (expression[j] == opening){
                bracketStack ++;
            }
            if (bracketStack == 1){
                return j;
            }
        }
    }else{
        // throw error
    }
}

string sanitise(string expression){
    if (isOpeningBracket(expression[0])){
        int closingBracket = findMatchingBracket(0, expression);
        if (closingBracket == expression.size() - 1){
            return expression.substr(1, closingBracket - 1);
        }else{
            return expression;
        }
    }else{
        return expression;
    }  
}

OpInfo::OpInfo(): op('~'), between{0, 0}{}

OpInfo::OpInfo(char op, int lhsBetween, int rhsBetween): op(op), between{lhsBetween, rhsBetween}{}

Scope::Scope(): type(ScopeType::None), sign(true), start(0), end(0){}

Scope::Scope(int start, int end): sign(true), start(start), end(end){}

void Scope::appendOperator(char op, int lhs, int rhs){
    OpInfo opWithinScope(op, lhs, rhs);
    ops.push_back(opWithinScope);
}

void Scope::appendOperand(string expression, int start, int end, bool pushBack){
    string operand = sanitise(expression.substr(start, (end - start) + 1));
    if (pushBack){
        operands.push_back(operand);
    }else{
        operands.insert(operands.begin(), operand);
    }
    
}



MParser::MParser(){}

shared_ptr<Expression>& MParser::getParseTree(){
    return parseTree;
}



shared_ptr<Symbol> MParser::buildSymbol(Scope scope, string expression){
    ScopeType type = scope.type;
    if (type == ScopeType::Atomic){
        if (expression.size() == 1 && isalpha(expression[0])){
            shared_ptr<Variable> variable = make_shared<Variable>(scope.sign, expression[0], parseTree);
            return variable;
        }else{
            int num = std::stoi(expression);
            shared_ptr<Constant> constant = make_shared<Constant>(scope.sign, num, parseTree);
            return constant;
        }
    }else if (type == ScopeType::Summation){
        shared_ptr<SumOp> sumOp = make_shared<SumOp>(scope.sign, parseTree);
        return sumOp;
    }else if (type == ScopeType::Multiplication){
        shared_ptr<MulOp> mulOp = make_shared<MulOp>(scope.sign, parseTree);
        return mulOp;
    }else if (type == ScopeType::Division){
        shared_ptr<DivOp> divOp = make_shared<DivOp>(scope.sign, parseTree);
        return divOp;
    }else if (type == ScopeType::Exponent){
        shared_ptr<Exponent> exponent = make_shared<Exponent>(scope.sign, parseTree);
        return exponent;
    }else if (type == ScopeType::Radical){
        shared_ptr<Radical> radical = make_shared<Radical>(scope.sign, parseTree);
        return radical;
    }else{
        // throw error
    }
}

shared_ptr<Symbol> MParser::buildAtom(string s){
    if (s.size() == 1 && isalpha(s[0])){
        shared_ptr<Variable> variable = make_shared<Variable>(s[0]);
        return variable;
    }else{
        int num = std::stoi(s);
        shared_ptr<Constant> constant = make_shared<Constant>(num);
        return constant;
    }
}

shared_ptr<Operation> MParser::buildOperation(ScopeType type){
    
    if (type == ScopeType::Summation){
        shared_ptr<SumOp> sumOp = make_shared<SumOp>();
        return sumOp;
    }else if (type == ScopeType::Multiplication){
        shared_ptr<MulOp> mulOp = make_shared<MulOp>();
        return mulOp;
    }else if (type == ScopeType::Division){
        shared_ptr<DivOp> divOp = make_shared<DivOp>();
        return divOp;
    }else if (type == ScopeType::Exponent){
        shared_ptr<Exponent> exponent = make_shared<Exponent>();
        return exponent;
    }else if (type == ScopeType::Radical){
        shared_ptr<Radical> radical = make_shared<Radical>();
        return radical;
    }else{
        // throw
    }
}

shared_ptr<Operation> MParser::buildOperation(char c){
    if (c == '+' || c == '-'){
        shared_ptr<SumOp> sumOp = make_shared<SumOp>();
        return sumOp;
    }else if (c == '*'){
        shared_ptr<MulOp> mulOp = make_shared<MulOp>();
        return mulOp;
    }else if (c == '/'){
        shared_ptr<DivOp> divOp = make_shared<DivOp>();
        return divOp;
    }else{
        // throw
    }
}

// shared_ptr<AuxOp> MParser::buildAuxOperation(char c, string expression){
//     shared_ptr<Symbol> root = shared_ptr<Symbol>();
//     parseExpression(root, expression);
//     if (c == '^'){
//         shared_ptr<AuxOp> exponent = make_shared<Exponent>(root);
//         return exponent;
//     }else if (c == 'v'){
//         shared_ptr<AuxOp> radical = make_shared<Radical>(root);
//         return radical;
//     }else if (c == 'f'){
//         shared_ptr<AuxOp> function = make_shared<Function>(root);
//         return function;
//     }else{
//         // throw
//     }
// }

// shared_ptr<AuxOp> MParser::buildAuxOperationChain(vector<AuxOpInfo>& auxillaries, string expression){

//     // make sure that somewhere further up the chain there is a 
//     // check that makes it impossible to both take a radical and 
//     // an exponent at the same time

//     shared_ptr<AuxOp> rootAuxOp;

//     shared_ptr<AuxOp> currentAuxOp;
//     shared_ptr<AuxOp> previousAuxOp;

//     for (AuxOpInfo auxillary : auxillaries){
//         currentAuxOp = move(buildAuxOperation(auxillary.op, expression.substr(auxillary.start + 1, auxillary.end - (auxillary.start + 1))));

//         if (!rootAuxOp){
//             // root = current;
//             // previous = current;
//             rootAuxOp = currentAuxOp;
//             previousAuxOp = currentAuxOp;
//         }else{
//             // rootSymbol& = previous->getRoot()
//             // rootSymbol->appendAuxillary(current);
//             // previous = current;
//             shared_ptr<Symbol>& rootSymbol = previousAuxOp->getRoot();
//             shared_ptr<AuxOp> copiedCurrent = currentAuxOp->copy();
//             rootSymbol->appendAuxillary(copiedCurrent);
//             previousAuxOp = currentAuxOp;

//         }
//     }
//     if (rootAuxOp != nullptr){
//         shared_ptr<AuxOp> copiedRoot = rootAuxOp->copy();
//         return copiedRoot;
//     }else{
//         shared_ptr<AuxOp> null = shared_ptr<AuxOp>();
//         return null;
//         // return nullptr kinda deal
//     }
    
// }

bool MParser::isConstant(string expression, int start, int end){
    for (int i = start; i <= end; i ++){
        if (!isdigit(expression[i])){
            return false;
        }
    }
    return true;
}

bool MParser::isAtomic(string expression, int start, int end){
    bool hasDigit = false;
    bool hasChar = false;
    for (int i = start; i <= end; i ++){
        if (isalpha(expression[i])){
            if (hasChar){
                return false;
            }else{
                hasChar = true;
            }
            
        }else if (isdigit(expression[i])){
            hasDigit = true;
        }else{
            return false;
        }
    }
    if ((hasDigit && !hasChar) || (hasChar && !hasDigit)){
        return true;
    }else{
        return false;
    }
}

bool MParser::isMultiplied(string expression, int start, int end){
    if (end - start != 1){
        return false;
    }else{
        char symbolA = expression[start];
        char symbolB = expression[end];
        if (isClosingBracket(symbolA) && ((isalpha(symbolB) && symbolB != 'v') || isdigit(symbolB))){ // some subexpression times another value
            return true;
        }else if (isOpeningBracket(symbolB) && ((isalpha(symbolA) && symbolA != 'v') || isdigit(symbolA))){
            return true;
        }else if (isClosingBracket(symbolA) && isOpeningBracket(symbolB)){
            return true;
        }else if (isalpha(symbolA) && isalpha(symbolB) && symbolA != 'v' && symbolB != 'v'){
            return true;
        }else if (isdigit(symbolA) && isalpha(symbolB) && symbolA != 'v' && symbolB != 'v'){
            return true;
        }else{
            return false;
        }
    }
}

void MParser::setSymbolAsAuxillary(shared_ptr<Symbol>& symbol, AuxilliaryRelation relation){
    if (relation == AuxilliaryRelation::Exponent){
        symbol->setIsExponent(true);
    }else if (relation == AuxilliaryRelation::Radical){
        symbol->setIsRadical(true);
    }else if (relation == AuxilliaryRelation::Target){
        symbol->setIsTarget(true);
    }else{
        return;
    }
}

// void MParser::parseExpression(string expression){
//     parseTree = Expression();
//     shared_ptr<Symbol> root = shared_ptr<Symbol>();
//     parseExpression(root, expression);
//     parseTree.setRoot(root);
// }

void MParser::parseExpression(string expression){
    parseTree = make_shared<Expression>();

    
    Scope mainScope = findMainScope(expression);

    if (mainScope.type == ScopeType::Atomic){

        // string atom = expression.substr(mainScope.start + 1, mainScope.end - mainScope.start - 1);
        string atom = mainScope.operands[0];
        shared_ptr<Symbol> child = buildSymbol(mainScope, atom);

        // child->setParentExpression(parseTree);
        parseTree->setRoot(child);

        return;
        
    }else{

        shared_ptr<Symbol> child = buildSymbol(mainScope, expression);
        parseTree->setRoot(child);
        
        // child->setParentExpression(parseTree);

        // vector<string> operands = separateOperands(mainScope, expression);
        // vector<string> operands = mainScope.operands;

        for (int i = 0; i < mainScope.operands.size(); i ++){
            if (mainScope.type == ScopeType::Radical){
                if (i == 0){
                    parseExpression(child, AuxilliaryRelation::Radical, mainScope.operands[i]);
                }else{
                    parseExpression(child, AuxilliaryRelation::Target, mainScope.operands[i]);
                }
                
            }else if (mainScope.type == ScopeType::Exponent){
                if (i == 0){
                    parseExpression(child, AuxilliaryRelation::Target, mainScope.operands[i]);
                }else{
                    parseExpression(child, AuxilliaryRelation::Exponent, mainScope.operands[i]);
                }
            }else{
                parseExpression(child, AuxilliaryRelation::None, mainScope.operands[i]);
            }
        }

        
    }  
}

void MParser::parseExpression(shared_ptr<Symbol>& parent, AuxilliaryRelation parentRelation, string expression){    

    Scope mainScope = findMainScope(expression);


    // shared_ptr<AuxOp> auxOp = buildAuxOperationChain(mainScope.auxOps, expression);

    // bool emptyTree;
    // parent == nullptr ? emptyTree = true : emptyTree = false;

    if (mainScope.type == ScopeType::Atomic){
        // child = buildAtom(expression.substr(mainScope.start + 1, mainScope.end - mainScope.start - 1));
        // child->appendAuxillary(auxOp);

        // string atom = expression.substr(mainScope.start + 1, mainScope.end - mainScope.start - 1);
        string atom = mainScope.operands[0];
        shared_ptr<Symbol> child = buildSymbol(mainScope, atom);

        setSymbolAsAuxillary(child, parentRelation);

        // if (emptyTree){
        //     parent = move(child);
        // }else{
        //     parent->appendChild(child);
        // }
        parseTree->appendNode(parent, child);
        // child->setParent(parent);
        // parent->appendChild(child);

        return;
        
    }else{

        // child = buildOperation(mainScope.type);
        // child->appendAuxillary(auxOp);

        shared_ptr<Symbol> child = buildSymbol(mainScope, expression);

        // vector<string> operands = separateOperands(mainScope, expression);
        // vector<string> operands = mainScope.operands;

        setSymbolAsAuxillary(child, parentRelation);

        parseTree->appendNode(parent, child);
        // vector<string> auxillaries = separateAuxillaries(mainScope, expression);  

        // for (string auxillary : auxillaries){
            
        // }
        
        
        for (int i = 0; i < mainScope.operands.size(); i ++){
            if (mainScope.type == ScopeType::Radical){
                if (i == 0){
                    parseExpression(child, AuxilliaryRelation::Radical, mainScope.operands[i]);
                }else{
                    parseExpression(child, AuxilliaryRelation::Target, mainScope.operands[i]);
                }
                
            }else if (mainScope.type == ScopeType::Exponent){
                if (i == 0){
                    parseExpression(child, AuxilliaryRelation::Target, mainScope.operands[i]);
                }else{
                    parseExpression(child, AuxilliaryRelation::Exponent, mainScope.operands[i]);
                }
            }else{
                parseExpression(child, AuxilliaryRelation::None, mainScope.operands[i]);
            }
        }



        // if (emptyTree){
        //     parent = move(child);
        // }else{
        //     parent->appendChild(child);
        // }
        
        // child->setParent(parent);
        // parent->appendChild(child);
    }  
}

void MParser::parseEquation(string equation){

}

void MParser::parseFunction(string function){

}

int MParser::findAuxOpApplicability(int auxOpStart, int auxOpEnd, int expressionMinMax, bool& cont){
    // if (atomCount == 1){
    //     if (auxOpEnd == expressionMinMax){
    //         cont = false;
    //         return auxOpStart;

    //     }else{
    //         cont = true;
    //         return auxOpEnd;
    //     }
    // }else{
    //     cont = true;
    //     return auxOpEnd;
    // }
    if (auxOpEnd == expressionMinMax){
            cont = false;
            return auxOpStart;

        }else{
            cont = true;
            return auxOpEnd;
        }
}



Scope MParser::scopeExpression(int i, string expression){ // applies to + and -

    Scope scope;
    scope.type = ScopeType::Summation;

    int breakF, breakB; 

    // breakF is the first character to include in the substr for the new operand forwards
    // breakB is the last operand to include in the substr for the new operand backwards

    if (expression[i] == '+'){
        breakF = i + 1;
        breakB = i - 1;
    }else if (expression[i] == '-'){
        breakF = i;
        breakB = i - 1;
    }
    

    bool forwards = true;
    bool backwards = true;

    int j = i + 1;
    int k = i - 1;

    while (true){
        

        if (forwards){
            if (expression[j] == '+'){
                // string operand = expression.substr(breakF, j - breakF);
                // scope.operands.push_back(operand);
                scope.appendOperand(expression, breakF, j - 1, true);
                breakF = j + 1;
                j ++;
            }else if (expression[j] == '-'){
                // string operand = expression.substr(breakF, j - breakF);
                // scope.operands.push_back(operand);
                scope.appendOperand(expression, breakF, j - 1, true);
                breakF = j;
                j ++;
            }else if (expression[j] == '(' || 
                        expression[j] == '{' || 
                        expression[j] == '['){
                j = findMatchingBracket(j, expression) + 1;
            }else if (expression[j] == ')' || 
                        expression[j] == '}' || 
                        expression[j] == ']'){
                scope.appendOperand(expression, breakF, j - 1, true);
                forwards = false;
            }else if (j >= expression.size()){
                // string operand = expression.substr(breakF, j - breakF);
                // scope.operands.push_back(operand);
                scope.appendOperand(expression, breakF, j - 1, true);
                forwards = false;
            }else{
                j ++;
            }
        }
        if (backwards){
            if (expression[k] == '+'){
                // string operand = expression.substr(k + 1, breakB - k - 1);
                // scope.operands.insert(scope.operands.begin(), operand);
                scope.appendOperand(expression, k + 1, breakB, false);
                breakB = k - 1;
                k --;
            }else if (expression[k] == '-'){
                // string operand = expression.substr(k, breakB - k); // (k, breakB - k)
                // scope.operands.insert(scope.operands.begin(), operand);
                scope.appendOperand(expression, k, breakB, false);
                breakB = k - 1;
                k --;
            }else if (isClosingBracket(expression[k])){

                k = findMatchingBracket(k, expression) - 1;

            }else if (isOpeningBracket(expression[k])){

                scope.appendOperand(expression, k + 1, breakB, false);
                if (expression[k - 1] == '-'){
                    scope.sign = false;
                }
                backwards = false;
            }else if (k < 0){
                if (breakB >= 0){
                    scope.appendOperand(expression, 0, breakB, false);
                }
                
                
                backwards = false;
            }else{
                k --;
            }
        }

        if (!forwards && !backwards){
            break;
        }

        
    }
    
    if (scope.operands.size() == 1 || scope.operands.size() == 0){
        Scope emptyScope;
        return emptyScope;
    }

    scope.start = k;
    scope.end = j;
    
    // scope.auxOps = scopeAuxOp(scope, expression);
    return scope;
}

// Scope MParser::scopeTerm(int lhs, int rhs, string expression){ // applies to * and atoms
    
//     Scope scope;

//     int breakF, breakB, j, k ;// j and k are set one further than breakF and breakB

//     breakF = rhs;
//     breakB = lhs;

    

//     // j = breakF + 1;
//     // k = breakB - 1;


//     expression[breakF] == '(' ? j = findMatchingBracket(breakF, expression) + 1 : j = breakF + 1;
//     expression[breakB] == ')' ? k = findMatchingBracket(breakB, expression) - 1 : k = breakB - 1;

    

//     bool digitParsedF, digitParsedB;
    
//     isdigit(expression[breakF]) ? digitParsedF = true : digitParsedF = false;
//     isdigit(expression[breakB]) ? digitParsedB = true : digitParsedB = false;
    


    
//     bool forwards = true;
//     bool backwards = true;

//     while (true){
//         if (forwards){
//             if (isalpha(expression[j]) && expression[j] != 'v'){
                

//                 scope.appendOperand(expression, breakF, j - 1, true);
            
//                 breakF = j;
                
//                 j ++;
//                 digitParsedF = false;
//             }else if (isdigit(expression[j])){
//                 if (!digitParsedF){
                    
//                     scope.appendOperand(expression, breakF, j - 1, true);
//                     breakF = j;
//                     digitParsedF = true;
//                 }
                
//                 j ++;

//             }else if (expression[j] == '('){
                
//                 scope.appendOperand(expression, breakF, j - 1, true);

//                 breakF = j;

//                 j = findMatchingBracket(j, expression) + 1;
//                 digitParsedF = false;

            
//             }else if (expression[j] == '^'){

//                 j = findMatchingBracket(j + 1, expression) + 1;

            
//                 // scope.appendOperand(expression, breakF, j - 1, true);
//                 // breakF = j;
//                 digitParsedF = false;


//             }else if (expression[j] == '['){
                
//                 scope.appendOperand(expression, breakF, j - 1, true);
//                 breakF = j;
//                 j = findMatchingBracket(j, expression) + 1;
//                 digitParsedF = false;

//             }else if (expression[j] == 'v'){
//                 if (expression[j + 1] == '('){
//                     j = findMatchingBracket(j + 1, expression) + 1;
//                 }else{
//                     j += 2;
//                 }
                
//                 // scope.appendOperand(expression, breakF, j - 1, true);
//                 // breakF = j;

//             }else if (j >= expression.size()){
                
//                 scope.appendOperand(expression, breakF, expression.size() - 1, true);
//                 forwards = false;
//             }else{
                
//                 scope.appendOperand(expression, breakF, j - 1, true);
//                 forwards = false;
//             }
//         }


//         if (backwards){
//             if (isalpha(expression[k]) && expression[k] != 'v'){
                
//                 scope.appendOperand(expression, k + 1, breakB, false);
//                 breakB = k;
                
//                 k --;
                
//                 digitParsedB = false;
//             }else if (isdigit(expression[k])){
                
//                 if (!digitParsedB){
                    
//                     scope.appendOperand(expression, k + 1, breakB, false);  
//                     breakB = k;
//                     digitParsedB = true;
                
//                 }

                
//                 k --;
//             }else if (expression[k] == ')'){
                 
//                 scope.appendOperand(expression, k + 1, breakB, false);
//                 breakB = k;

//                 k = findMatchingBracket(k, expression) - 1;
//                 digitParsedB = false;

            
//             }else if (expression[k] == 'v'){
//                 k = findMatchingBracket(k - 1, expression) - 1;

                
//                 // scope.appendOperand(expression, k + 1, breakB, false);
//                 // breakB = k;
//                 digitParsedF = false;

//             }else if (expression[k] == '}'){
                
//                 scope.appendOperand(expression, k + 1, breakB, false);
//                 breakB = k;
//                 k = findMatchingBracket(k, expression) - 1;
//                 digitParsedF = false;

//             }else if (expression[k] == '^'){
//                 if (expression[k - 1] == ')'){
//                     k = findMatchingBracket(k - 1, expression) - 1;
//                 }else{
//                     k -= 2;
//                 }
                
                
//                 // scope.appendOperand(expression, k + 1, breakB, false);
//                 // breakB = k;
            

//             }else if (k < 0){
                
//                 scope.appendOperand(expression, 0, breakB, false);  
                
//                 backwards = false;
//             }else{
                
//                 scope.appendOperand(expression, k + 1, breakB, false);  
//                 backwards = false;
//             }
//         }

//         if (!forwards && !backwards){
//             break;
//         }
//     }

//     if (expression[k] == '-'){
//         scope.sign = false;
//     }

//     if (scope.operands.size() == 1){
//         scope.type = ScopeType::Atomic;
//     }else{
//         scope.type = ScopeType::Multiplication;
//         scope.start = k;
//         scope.end = j;
        
//     }

    
    
//     // scope.auxOps = scopeAuxOp(scope, expression);
//     return scope;
// }

Scope MParser::scopeTerm(int lhs, int rhs, string expression){ // applies to * and atoms
    
    Scope scope;

    int breakF, breakB, j, k ; // j and k are set one further than breakF and breakB

    breakF = rhs;
    breakB = lhs;

    

    j = breakF;
    k = breakB;
    


    
    bool forwards = true;
    bool backwards = true;

    while (true){
        if (forwards){
            if (isMultiplied(expression, j, j + 1)){
                

                scope.appendOperand(expression, breakF, j, true);

                j ++;
            
                breakF = j;

                
                
                
            }else{
                if (isOpeningBracket(expression[j])){
                    j = findMatchingBracket(j, expression);
                    if (expression[j + 1] == 'v'){
                        if (expression[j + 2] == '('){
                            j = findMatchingBracket(j + 2, expression);
                        }else{
                            j += 2;
                        }
                    }else if (expression[j + 1] == '^'){
                        j = findMatchingBracket(j + 2, expression);
                    }
                    
                }else if (expression[j] == '+' || expression[j] == '-' || expression[j] == '/' || j >= expression.size()){
                    scope.appendOperand(expression, breakF, j - 1, true);
                    forwards = false;
                }else{
                    j ++;
                    if (isClosingBracket(expression[j])){
                        scope.appendOperand(expression, breakF, j - 1, true);
                        forwards = false;
                    }
                }
            }
        }


        if (backwards){
            if (isMultiplied(expression, k - 1, k)){
                scope.appendOperand(expression, k, breakB, false);

                k --;
            
                breakB = k;
            }else{
                if (isClosingBracket(expression[k])){
                    k = findMatchingBracket(k, expression);
                    if (expression[k - 1] == '^'){
                        if (expression[k - 2] == ')'){
                            k = findMatchingBracket(k - 2, expression);
                        }else{
                            k -= 2;
                        }
                    }else if (expression[k - 1] == 'v'){
                        k = findMatchingBracket(k - 2, expression);
                    }
                    
                }else if (expression[k] == '+' || expression[k] == '-' || expression[k] == '/' || k < 0){
                    scope.appendOperand(expression, k + 1, breakB, false);
                    backwards = false;
                }else{
                    k --;
                    if (isOpeningBracket(expression[k])){
                        scope.appendOperand(expression, k + 1, breakB, false);
                        backwards = false;  
                    }
                }
            }
        }

        if (!forwards && !backwards){
            break;
        }
    }

    if (expression[k] == '-'){
        scope.sign = false;
    }

    scope.type = ScopeType::Multiplication;
    scope.start = k;
    scope.end = j;

    
    
    // scope.auxOps = scopeAuxOp(scope, expression);
    return scope;
}

Scope MParser::scopeRational(int i, string expression){

    Scope scope;
    scope.type = ScopeType::Division;
    scope.appendOperator('/', i - 1, i + 1);

    int breakF, breakB, j, k;

    breakF = i + 1;
    breakB = i - 1;

    j = breakF;
    k = breakB;

    bool forwards = true;
    bool backwards = true;

    while (true){
        if (forwards){
            if (isalpha(expression[j]) || isdigit(expression[j])){
                j ++;
            }else if (expression[j] == '('){
                j = findMatchingBracket(j, expression) + 1;
            }else if (expression[j] == '['){
                j = findMatchingBracket(j, expression) + 2;
            }else if (expression[j] == '^'){
                j = findMatchingBracket(j + 1, expression) + 1;
            }else if (j >= expression.size()){
                scope.appendOperand(expression, breakF, expression.size() - 1, true);
                forwards = false;
            }else{
                scope.appendOperand(expression, breakF, j - 1, true);
                forwards = false;
            }
        }
        if (backwards){
            if (isalpha(expression[k]) || isdigit(expression[k])){
                k --;
            }else if (expression[k] == ')'){
                k = findMatchingBracket(k, expression) - 1;
            }else if (expression[k] == '}'){
                k = findMatchingBracket(k, expression) - 2;
            }else if (expression[k] == 'v'){
                k = findMatchingBracket(k - 1, expression) - 1;
            }else if (k < 0){
                scope.appendOperand(expression, 0, breakB, false);
                backwards = false;
            }else{
                scope.appendOperand(expression, k + 1, breakB, false);
                backwards = false;
            }
        }

        if (!forwards && !backwards){
            break;
        }
    }

    if (expression[k] == '-' && expression[i + 1] == '-'){
        scope.sign = true;
    }else if (expression[k] == '-' || expression[i + 1] == '-'){
        scope.sign = false;
    }
    
    
    scope.start = k;
    scope.end = j;
    // scope.auxOps = scopeAuxOp(scope, expression);
    return scope;

}

Scope MParser::scopeAuxOp(int i, string expression){
    Scope scope;

    int breakF, breakB, j, k;

    breakF = i + 1;
    breakB = i - 1;
    j = breakF;
    k = breakB;

    if (expression[i] == '^'){
        scope.type = ScopeType::Exponent;
        
        j = findMatchingBracket(j, expression) + 1;

        scope.appendOperator('^', i - 1, i + 1);
        scope.appendOperand(expression, breakF + 1, j - 2, true);

        if (isalpha(expression[k])){
            k --;
            scope.appendOperand(expression, k + 1, breakB, false);
        }else if (isdigit(expression[k])){
            k --;
            while (isdigit(expression[k])){
                k --;
            }
            scope.appendOperand(expression, k + 1, breakB, false);
        }else if (expression[k] == ')'){
            k = findMatchingBracket(k, expression) - 1;
            scope.appendOperand(expression, k + 2, breakB - 1, false);
        }else{
            // throw
        }
        
    }else if (expression[i] == 'v'){
        scope.type = ScopeType::Radical;
        
        k = findMatchingBracket(k, expression) - 1;

        scope.appendOperator('v', i - 1, i + 1);
        scope.appendOperand(expression, k + 2, breakB - 1, false);

        if (isalpha(expression[j])){
            j ++;
            scope.appendOperand(expression, breakF, j - 1, true);
        }else if (isdigit(expression[j])){
            j ++;
            while (isdigit(expression[j])){
                j ++;
            }
            scope.appendOperand(expression, breakF, j - 1, true);
        }else if (expression[j] == '('){
            j = findMatchingBracket(j, expression) + 1;
            scope.appendOperand(expression, breakF + 1, j - 2, true);
        }else{
            // throw
        }

    }

    if (expression[k] == '-'){
        scope.sign = false;
    }
    scope.start = k;
    scope.end = j;
    return scope;
}

// vector<AuxOpInfo> MParser::scopeAuxOp(Scope parentScope, string expression){

//     vector<AuxOpInfo> auxOpScopes;

//     int j, k;

//     expression[parentScope.end] == ')' ? j = parentScope.end + 1 : j = parentScope.end;
//     expression[parentScope.start] == '(' ? k = parentScope.start - 1 : k = parentScope.start;

//     while(expression[j] == '^'){
//         AuxOpInfo auxOpScope;
//         auxOpScope.op = '^';
//         auxOpScope.start = j + 1;
//         auxOpScope.end = findMatchingBracket(j + 1, expression);
//         auxOpScopes.push_back(auxOpScope);
//         j = auxOpScope.end + 1;
//     }

//     while (expression[k] == 'v'){
//         AuxOpInfo auxOpScope;
//         auxOpScope.op = 'v';
//         auxOpScope.start = findMatchingBracket(k - 1, expression);
//         auxOpScope.end = k - 1;
//         auxOpScopes.push_back(auxOpScope);
//         k = auxOpScope.start - 1;
//     }

//     return auxOpScopes;
    
// }

// vector<AuxOpInfo> MParser::scopeAuxOp(int i, string expression){

//     vector<AuxOpInfo> auxOpScopes;

//     int j = i;
//     int k = i;


//     while(expression[j] == '^'){
//         AuxOpInfo auxOpScope;
//         auxOpScope.op = '^';
//         auxOpScope.start = j + 1;
//         auxOpScope.end = findMatchingBracket(j + 1, expression);
//         auxOpScopes.push_back(auxOpScope);
//         j = auxOpScope.end + 1;
//     }

//     while (expression[k] == 'v'){
//         AuxOpInfo auxOpScope;
//         auxOpScope.op = 'v';
//         auxOpScope.start = findMatchingBracket(k - 1, expression);
//         auxOpScope.end = k - 1;
//         auxOpScopes.push_back(auxOpScope);
//         k = auxOpScope.start - 1;
//     }

//     return auxOpScopes;
    
// }


Scope MParser::scopeConstant(int i, string expression){
    Scope scope;

    int j = i + 1;
    int k = i - 1;

    bool forwards = true;
    bool backwards = true;

    while(true){
        if (forwards){
            if (isdigit(expression[j])){
                j ++;
            // }else if (expression[j] == '^'){
            //     scope.addAuxillary('^', j + 1, findMatchingBracket(j + 1, expression));
            //     forwards = false;
            }else{
                forwards = false;
            }
        }

        if (backwards){
            if(isdigit(expression[k])){
                k --;
            // }else if (expression[j] == 'v'){
            //     scope.addAuxillary('v', k - 1, findMatchingBracket(k - 1, expression));
            //     backwards = false;
            }else{
                backwards = false;
            }
        }

        if (!forwards && !backwards){
            break;
        }
    }

    if (expression[k] == '-'){
        scope.sign = false;
    }
    // scope.operands.push_back(expression.substr(k + 1, j - k));
    scope.appendOperand(expression, k + 1, j - 1, true);
    scope.type = ScopeType::Atomic;
    scope.start = k;
    scope.end = j;
    return scope;
}

// if given character, then finds the extent of the multiplication, if it only consists of one char
// then it is not a multiplication, it is atomic, if given an operator, either + or /, finds the 
// operands of the operator, if given a ( finds the closing bracker, and vice versa

Scope MParser::findScope(int i, string expression){

    Scope scope;

    char symbol = expression[i];

    if (symbol == '+' || symbol == '-'){

        return scopeExpression(i, expression);

    // }else if (isalpha(symbol) || (isdigit(symbol) && !isdigit(expression[i - 1]) && symbol != 'v')){

    //     return scopeTerm(i, expression);

    }else if (isMultiplied(expression, i, i + 1)){

        return scopeTerm(i, i + 1, expression);

    }else if (isMultiplied(expression, i - 1, i)){

        return scopeTerm(i - 1, i, expression);

    }else if (!isMultiplied(expression, i, i + 1) && !isMultiplied(expression, i - 1, i) && isdigit(expression[i])){ // is atomic constant

        return scopeConstant(i, expression);

    }else if (!isMultiplied(expression, i, i + 1) && !isMultiplied(expression, i - 1, i) && isalpha(expression[i]) && expression[i] != 'v'){ // is atomic variable

        scope.start = i - 1;
        scope.end = i + 1;
        scope.type = ScopeType::Atomic;
        expression[scope.start] == '-' ? scope.sign = false : scope.sign = true; 
        string variable = "";
        variable += expression[i];
        scope.operands.push_back(variable);
        return scope;

    }else if (symbol == '/'){

        return scopeRational(i, expression);

    }else if (symbol == '^' || symbol  == 'v'){

        return scopeAuxOp(i, expression);

    }else{

        return scope; // return empty scope;

    }
}

Scope MParser::findMainScope(string expression){
    Scope mainScope;
    mainScope.start = 0;
    mainScope.end = 0;
    for (int i = 0; i < expression.size(); i ++){
        if (isalpha(expression[i]) || 
                isdigit(expression[i]) || 
                expression[i] == '+' || 
                expression[i] == '-' || 
                expression[i] == '/' || 
                expression[i] == '^' || 
                expression[i] == 'v'){
            Scope ithScope = findScope(i, expression);
            if ((ithScope.end - ithScope.start) > (mainScope.end - mainScope.start)){
                mainScope = ithScope;
            } 
        }
    }
    return mainScope;
}

vector<string> MParser::separateOperands(Scope& scope, string expression){
    
    vector<string> operands;

    string sanitised = sanitise(expression); // remove negative sign of main operation, but not negative sign of operands
    if (sanitised != expression){
        scope = findMainScope(sanitised);
        expression = sanitised;
    }
    

    if (scope.type == ScopeType::Atomic){

        operands.push_back(expression);
        return operands;
    
    }else{
        int j, k, offset1, offset2, min, max, iterations;

        if (expression[0] == '-'){
            if (scope.type == ScopeType::Summation){// && expression[1] != '('){ // include the - in the operands
                offset1 = 1;
                offset2 = 0;
                min = 0;
                max = scope.ops.size();
                iterations = scope.ops.size();
            }else{ // dont include the - in the operands
                offset1 = 0;
                offset2 = -1;
                //expression[1] == '(' ? min = 2 : min = 1;
                min = 1;
                max = scope.ops.size() + 1;
                iterations = scope.ops.size() + 1;
            }
        }else{
            offset1 = 0;
            offset2 = -1;
            min = 0;
            max = scope.ops.size() + 1;
            iterations = scope.ops.size() + 1;
        }

        for (int i = 0; i < max; i ++){
            if (i == 0){
                j = min;
                k = scope.ops[i + offset1].between.first + (1 - min);
            }else if (i == scope.ops.size()){
                j = scope.ops[i + offset2].between.second;
                k = expression.size() - j;
            }else{
                j = scope.ops[i + offset2].between.second;
                k = scope.ops[i + offset1].between.first + 1 - j;
            }
            string newOperand = expression.substr(j, k);
            operands.push_back(sanitise(newOperand));
        }








        // if (scope.type == ScopeType::Summation && scope.ops[0].between.second == 0){ // starts with an operator
        //     for (int i = 0; i < scope.ops.size(); i ++){
        //         if (i == 0){
        //             j = 0;
        //             k = scope.ops[i + 1].between.first + 1;
        //         }else if (i == scope.ops.size()){
        //             j = scope.ops[i].between.second;
        //             k = expression.size() - j;
        //         }else{
        //             j = scope.ops[i].between.second;
        //             k = scope.ops[i + 1].between.first + 1 - j;
        //         }
        //         string newOperand = expression.substr(j, k);
        //         operands.push_back(sanitise(newOperand));
        //     }
            
        // }else{ // starts with an operand
        //     for (int i = 0; i <= scope.ops.size(); i ++){

        //         if (i == 0){
        //             expression[0] == '-' ? j = 1 : j = 0;
        //             k = scope.ops[i].between.first + 1;
        //         }else if (i == scope.ops.size()){
        //             j = scope.ops[i - 1].between.second;
        //             k = expression.size() - j;
        //         }else{
        //             j = scope.ops[i - 1].between.second;
        //             k = scope.ops[i].between.first + 1 - j;
        //         }
                
                
        //         string newOperand = expression.substr(j, k);
        //         operands.push_back(sanitise(newOperand));
                
        //     }
        // }

        
        return operands;
    }

    
}

pair<string, vector<string>> MParser::separateAuxillaries(Scope& scope, string expression){
    pair<string, vector<string>> auxillaryPair;
    vector<string> auxillaries = separateOperands(scope, expression);
    auxillaryPair.first = auxillaries[0];
    auxillaries.erase(auxillaries.begin());
    auxillaryPair.second = auxillaries;
    return auxillaryPair;
}

// vector<string> MParser::separateAuxillaries(Scope& scope, string expression){

//     vector<string> auxillaries;

//     for (int i = 0; i < scope.auxOps.size(); i ++){
//         AuxOpInfo currentInfo = scope.auxOps[i];
//         string auxillary = expression.substr(currentInfo.start + 1, (currentInfo.end - 1) - (currentInfo.start + 1));
//         auxillaries.push_back(auxillary);
//     }

//     return auxillaries;
// }

