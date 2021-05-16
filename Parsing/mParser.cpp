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



MParser::MParser(){}

Expression MParser::getParseTree(){
    return move(parseTree);
}

bool MParser::isOpeningBracket(char bracket){
    if (bracket == '(' ||
        bracket == '{' || 
        bracket == '['){
        return true;
    }else{
        return false;
    }
}

bool MParser::isClosingBracket(char bracket){
    if (bracket == ')' ||
        bracket == '}' || 
        bracket == ']'){
        return true;
    }else{
        return false;
    }
}

unique_ptr<Symbol> MParser::buildSymbol(Scope scope, string expression){
    ScopeType type = scope.type;
    if (type == ScopeType::Atomic){
        if (expression.size() == 1 && isalpha(expression[0])){
            unique_ptr<Variable> variable = make_unique<Variable>(scope.sign, expression[0]);
            return variable;
        }else{
            int num = std::stoi(expression);
            unique_ptr<Constant> constant = make_unique<Constant>(scope.sign, num);
            return constant;
        }
    }else if (type == ScopeType::Summation){
        unique_ptr<SumOp> sumOp = make_unique<SumOp>(scope.sign);
        return sumOp;
    }else if (type == ScopeType::Multiplication){
        unique_ptr<MulOp> mulOp = make_unique<MulOp>(scope.sign);
        return mulOp;
    }else if (type == ScopeType::Division){
        unique_ptr<DivOp> divOp = make_unique<DivOp>(scope.sign);
        return divOp;
    }else if (type == ScopeType::Exponent){
        unique_ptr<Exponent> exponent = make_unique<Exponent>(scope.sign);
        return exponent;
    }else if (type == ScopeType::Radical){
        unique_ptr<Radical> radical = make_unique<Radical>(scope.sign);
        return radical;
    }else{
        // throw error
    }
}

unique_ptr<Symbol> MParser::buildAtom(string s){
    if (s.size() == 1 && isalpha(s[0])){
        unique_ptr<Variable> variable = make_unique<Variable>(s[0]);
        return variable;
    }else{
        int num = std::stoi(s);
        unique_ptr<Constant> constant = make_unique<Constant>(num);
        return constant;
    }
}

unique_ptr<Operation> MParser::buildOperation(ScopeType type){
    
    if (type == ScopeType::Summation){
        unique_ptr<SumOp> sumOp = make_unique<SumOp>();
        return sumOp;
    }else if (type == ScopeType::Multiplication){
        unique_ptr<MulOp> mulOp = make_unique<MulOp>();
        return mulOp;
    }else if (type == ScopeType::Division){
        unique_ptr<DivOp> divOp = make_unique<DivOp>();
        return divOp;
    }else if (type == ScopeType::Exponent){
        unique_ptr<Exponent> exponent = make_unique<Exponent>();
        return exponent;
    }else if (type == ScopeType::Radical){
        unique_ptr<Radical> radical = make_unique<Radical>();
        return radical;
    }else{
        // throw
    }
}

unique_ptr<Operation> MParser::buildOperation(char c){
    if (c == '+' || c == '-'){
        unique_ptr<SumOp> sumOp = make_unique<SumOp>();
        return sumOp;
    }else if (c == '*'){
        unique_ptr<MulOp> mulOp = make_unique<MulOp>();
        return mulOp;
    }else if (c == '/'){
        unique_ptr<DivOp> divOp = make_unique<DivOp>();
        return divOp;
    }else{
        // throw
    }
}

// unique_ptr<AuxOp> MParser::buildAuxOperation(char c, string expression){
//     unique_ptr<Symbol> root = unique_ptr<Symbol>();
//     parseExpression(root, expression);
//     if (c == '^'){
//         unique_ptr<AuxOp> exponent = make_unique<Exponent>(root);
//         return exponent;
//     }else if (c == 'v'){
//         unique_ptr<AuxOp> radical = make_unique<Radical>(root);
//         return radical;
//     }else if (c == 'f'){
//         unique_ptr<AuxOp> function = make_unique<Function>(root);
//         return function;
//     }else{
//         // throw
//     }
// }

// unique_ptr<AuxOp> MParser::buildAuxOperationChain(vector<AuxOpInfo>& auxillaries, string expression){

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
//             unique_ptr<Symbol>& rootSymbol = previousAuxOp->getRoot();
//             unique_ptr<AuxOp> copiedCurrent = currentAuxOp->copy();
//             rootSymbol->appendAuxillary(copiedCurrent);
//             previousAuxOp = currentAuxOp;

//         }
//     }
//     if (rootAuxOp != nullptr){
//         unique_ptr<AuxOp> copiedRoot = rootAuxOp->copy();
//         return copiedRoot;
//     }else{
//         unique_ptr<AuxOp> null = unique_ptr<AuxOp>();
//         return null;
//         // return nullptr kinda deal
//     }
    
// }

bool MParser::isVariable(string expression, int start, int end){
    return false;
}

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

string MParser::sanitise(string expression, string expressionType){
    if (isOpeningBracket(expression[0])){
        int closingBracket = findMatchingBracket(0, expression);
        if (closingBracket == expression.size() - 1){
            return expression.substr(1, closingBracket - 1);
        }else{
            return expression;
        }
    }
    
    
    if (expressionType == "operation"){
        if (expression[0] == '-' && expression[1] == '('){
            if (findMatchingBracket(1, expression) == expression.size() - 1){
                return expression.substr(2, expression.size() - 3);
            }else{
                return expression;
            }
            
        }else if (expression[0] == '-'){
            if (isAtomic(expression, 1, expression.size() - 1)){
                return expression.substr(1, expression.size() - 1);
            }else{
                return expression;
            }
            
        }else{
            return expression;
        }
    }
    return expression;
    
    
    
}


void MParser::setSymbolAsAuxillary(unique_ptr<Symbol>& symbol, AuxilliaryRelation relation){
    if (relation == AuxilliaryRelation::Exponent){
        symbol->setAsExponent(true);
    }else if (relation == AuxilliaryRelation::Radical){
        symbol->setAsRadical(true);
    }else if (relation == AuxilliaryRelation::Target){
        symbol->setAsTarget(true);
    }else{
        return;
    }
}

// void MParser::parseExpression(string expression){
//     parseTree = Expression();
//     unique_ptr<Symbol> root = unique_ptr<Symbol>();
//     parseExpression(root, expression);
//     parseTree.setRoot(root);
// }

void MParser::parseExpression(string expression){
    parseTree = Expression();
    
    Scope mainScope = findMainScope(expression);


    if (mainScope.type == ScopeType::Atomic){

        string atom = expression.substr(mainScope.start + 1, mainScope.end - mainScope.start - 1);
        unique_ptr<Symbol> child = buildSymbol(mainScope, atom);

        parseTree.setRoot(child);

        return;
        
    }else{

        unique_ptr<Symbol> child = buildSymbol(mainScope, expression);

        vector<string> operands = separateOperands(mainScope, expression);

        for (int i = 0; i < operands.size(); i ++){
            if (mainScope.type == ScopeType::Radical){
                if (i == 0){
                    parseExpression(child, AuxilliaryRelation::Radical, operands[i]);
                }else{
                    parseExpression(child, AuxilliaryRelation::Target, operands[i]);
                }
                
            }else if (mainScope.type == ScopeType::Exponent){
                if (i == 0){
                    parseExpression(child, AuxilliaryRelation::Target, operands[i]);
                }else{
                    parseExpression(child, AuxilliaryRelation::Exponent, operands[i]);
                }
            }else{
                parseExpression(child, AuxilliaryRelation::None, operands[i]);
            }
        }

        parseTree.setRoot(child);
    }  
}

void MParser::parseExpression(unique_ptr<Symbol>& parent, AuxilliaryRelation parentRelation, string expression){    

    Scope mainScope = findMainScope(expression);


    // unique_ptr<AuxOp> auxOp = buildAuxOperationChain(mainScope.auxOps, expression);

    // bool emptyTree;
    // parent == nullptr ? emptyTree = true : emptyTree = false;

    if (mainScope.type == ScopeType::Atomic){
        // child = buildAtom(expression.substr(mainScope.start + 1, mainScope.end - mainScope.start - 1));
        // child->appendAuxillary(auxOp);

        string atom = expression.substr(mainScope.start + 1, mainScope.end - mainScope.start - 1);
        unique_ptr<Symbol> child = buildSymbol(mainScope, expression);

        setSymbolAsAuxillary(child, parentRelation);

        // if (emptyTree){
        //     parent = move(child);
        // }else{
        //     parent->appendChild(child);
        // }

        parent->appendChild(child);

        return;
        
    }else{

        // child = buildOperation(mainScope.type);
        // child->appendAuxillary(auxOp);

        unique_ptr<Symbol> child = buildSymbol(mainScope, expression);

        vector<string> operands = separateOperands(mainScope, expression);

        setSymbolAsAuxillary(child, parentRelation);
        // vector<string> auxillaries = separateAuxillaries(mainScope, expression);  

        // for (string auxillary : auxillaries){
            
        // }
        
        for (int i = 0; i < operands.size(); i ++){
            if (mainScope.type == ScopeType::Radical){
                if (i == 0){
                    parseExpression(child, AuxilliaryRelation::Radical, operands[i]);
                }else{
                    parseExpression(child, AuxilliaryRelation::Target, operands[i]);
                }
                
            }else if (mainScope.type == ScopeType::Exponent){
                if (i == 0){
                    parseExpression(child, AuxilliaryRelation::Target, operands[i]);
                }else{
                    parseExpression(child, AuxilliaryRelation::Exponent, operands[i]);
                }
            }else{
                parseExpression(child, AuxilliaryRelation::None, operands[i]);
            }
        }



        // if (emptyTree){
        //     parent = move(child);
        // }else{
        //     parent->appendChild(child);
        // }
        parent->appendChild(child);
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

int MParser::findMatchingBracket(int i, string expression){

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
            if (bracketStack == 1){int rootOperator = findMatchingBracket(j, expression) + 1;
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

Scope MParser::scopeExpression(int i, string expression){ // applies to + and -

    Scope scope;
    scope.type = ScopeType::Summation;

    int lastBreakF, lastBreakB;
    if (expression[i] == '+'){
        scope.appendOperator(expression[i], i - 1, i + 1);
        lastBreakF = i + 1;
        lastBreakB = i - 1;
    }else if (expression[i] == '-'){
        scope.appendOperator(expression[i], i - 1, i);
        lastBreakF = i;
        lastBreakB = i;
    }
    

    bool forwards = true;
    bool backwards = true;

    int j = i + 1;
    int k = i - 1;

    int lhsBracketStack = 0;
    int rhsBracketStack = 0;

    while (true){
        
        if (j >= expression.size()){
            string operand = expression.substr(lastBreakF, j - lastBreakF);
            scope.operands.push_back(operand);
            forwards = false;
        }
        if (k < 0){
            string operand = expression.substr(k + 1, lastBreakB - k - 1);
            scope.operands.insert(scope.operands.begin(), operand);
            backwards = false;
        }
        if (!forwards && !backwards){
            break;
        }

        if (forwards){
            if (expression[j] == '+'){
                string operand = expression.substr(lastBreakF, j - lastBreakF);
                scope.operands.push_back(operand);
                lastBreakF = j + 1;
                scope.appendOperator(expression[j], j - 1, j + 1);
                j ++;
            }else if (expression[j] == '-'){
                string operand = expression.substr(lastBreakF, j - lastBreakF);
                scope.operands.push_back(operand);
                lastBreakF = j;
                scope.appendOperator(expression[j], j - 1, j);
                j ++;
            }else if (expression[j] == '(' || 
                        expression[j] == '{' || 
                        expression[j] == '['){
                j = findMatchingBracket(j, expression) + 1;
            }else if (expression[j] == ')' || 
                        expression[j] == '}' || 
                        expression[j] == ']'){
                forwards = false;
            }else{
                j ++;
            }
        }
        if (backwards){
            if (expression[k] == '+'){
                string operand = expression.substr(k + 1, lastBreakB - k - 1);
                scope.operands.insert(scope.operands.begin(), operand);
                lastBreakB = k - 1;
                scope.appendOperator(expression[k], k - 1, k + 1);
                k --;
            }else if (expression[k] == '-'){
                string operand = expression.substr(k, lastBreakB - k); // (k, lastBreakB - k)
                scope.operands.insert(scope.operands.begin(), operand);
                lastBreakB = k;
                scope.appendOperator(expression[k], k - 1, k);
                k --;
            }else if (expression[k] == ')' || 
                        expression[k] == '}' || 
                        expression[k] == ']'){
                k = findMatchingBracket(k, expression) - 1;
            }else if (expression[k] == '(' || 
                        expression[k] == '{' || 
                        expression[k] == '['){
                if (expression[k - 1] == '-'){
                    scope.sign = false;
                }
                backwards = false;
            }else{
                k --;
            }
        }

        
    }
    
    if (scope.ops.size() == 1 && scope.ops[0].between.second == k + 1){
        Scope emptyScope;
        return emptyScope;
    }

    scope.start = k;
    scope.end = j;
    // scope.auxOps = scopeAuxOp(scope, expression);
    return scope;
}

Scope MParser::scopeTerm(int i, string expression){ // applies to * and atoms
    
    Scope scope;

    int operandCount = 1;

    int j = i + 1;
    int k = i - 1;
    int tmpj = j;
    int tmpk = k;
    
    bool forwards = true;
    bool backwards = true;
    bool appendOperatorForwards = true;
    bool appendOperatorBackwards = true;
    while (true){
        if (forwards){
            if (isalpha(expression[j]) && expression[j] != 'v'){
                if (j != i){
                    if (appendOperatorForwards){
                        scope.appendOperator('*', j - 1, j);
                    }else{
                        appendOperatorForwards = true;
                    }
                    operandCount ++;
                }
                j ++;
            }else if (isdigit(expression[j])){
                j = scopeConstant(j, expression).end;
                tmpj = j;
                // operandCount ++;
            }else if (expression[j] == '('){
                if (appendOperatorForwards){
                    scope.appendOperator('*', j - 1, j);
                }else{
                    appendOperatorForwards = true;
                }
                
                j = findMatchingBracket(j, expression) + 1;
                operandCount ++;
            // }else if (expression[j] == ')'){
            //     vector<AuxOpInfo> exponents = scopeAuxOp(j + 1, expression);
            //     for (AuxOpInfo exponent : exponents){
            //         scope.auxOps.push_back(exponent);
            //     }
            //     forwards = false;
            }else if (expression[j] == '['){
                scope.appendOperator('*', j - 1, j);
                // int rootOperator = findMatchingBracket(j, expression) + 1;
                // j = scopeAuxOp(rootOperator, expression).end;
                j = findMatchingBracket(j, expression) + 2;
                appendOperatorForwards = false;
                // if (expression[j] == '('){
                //     j = findMatchingBracket(j, expression) + 1;
                //     operandCount ++;
                // }
            }else if (expression[j] == '^'){

                // int tmp = j;
                // while (expression[tmp] == '^'){
                //     tmp = findMatchingBracket(tmp + 1, expression) + 1;
                // }
                // if (tmp >= expression.size() || isClosingBracket(expression[tmp])){
                //     forwards = false;
                // }else{
                //     j = tmp;
                // }

                // int tmp = findMatchingBracket(j + 1, expression) + 1;

                // (tmp >= expression.size() || isClosingBracket(expression[tmp])) ? forwards = false : j = tmp;

                tmpj = j;
                j = findMatchingBracket(j + 1, expression) + 1;



            }else{
                forwards = false;
            }
        }
        if (backwards){
            if (isalpha(expression[k]) && expression[k] != 'v'){
                if (k != i){
                    if(appendOperatorBackwards){
                        scope.appendOperator('*', k, k + 1);
                    }else{
                        appendOperatorBackwards = true;
                    }
                    operandCount ++;
                }
                k --;
            }else if (isdigit(expression[k])){
                k = scopeConstant(k, expression).start;
                tmpk = k;
                // operandCount ++;
            }else if (expression[k] == ')'){
                if(appendOperatorBackwards){
                    scope.appendOperator('*', k, k + 1);
                }else{
                    appendOperatorBackwards = true;
                }
                
                k = findMatchingBracket(k, expression) - 1;
                operandCount ++;
            // }else if (expression[k] == '('){
            //     vector<AuxOpInfo> radicals = scopeAuxOp(k - 1, expression);
            //     for (AuxOpInfo radical : radicals){
            //         scope.auxOps.insert(scope.auxOps.begin(), radical);
            //     }
            //     backwards = false;
            }else if (expression[k] == '}'){
                scope.appendOperator('*', k, k + 1);
                // int exponentOperator = findMatchingBracket(k, expression) - 1;
                // k = scopeAuxOp(exponentOperator, expression).start;
                k = findMatchingBracket(k, expression) - 2;
                appendOperatorBackwards = false;
                // if (expression[k] == ')'){
                //     k = findMatchingBracket(k, expression) - 1;
                //     operandCount ++;
                // }
            }else if (expression[k] == 'v'){
                // int tmp = j;
                // while(expression[tmp] == 'v'){
                //     tmp = findMatchingBracket(tmp - 1, expression) - 1;
                // }
                // if (tmp < 0 || isOpeningBracket(expression[tmp])){
                //     backwards = false;
                // }else{
                //     k = tmp;
                // }

                // int tmp = findMatchingBracket(k - 1, expression) - 1;

                // (tmp < 0 || isOpeningBracket(expression[tmp])) ? backwards = false : k = tmp;

                tmpk = k;
                k = findMatchingBracket(k - 1, expression) - 1;

            }else{
                backwards = false;
            }
        }


        if (j >= expression.size()){
            forwards = false;
        }
        if (k < 0){
            backwards = false;
        }
        if (!forwards && !backwards){
            break;
        }
    }

    if (expression[k] == '-'){
        scope.sign = false;
    }

    if (operandCount == 1){
        scope.type = ScopeType::Atomic;
        scope.start = tmpk;
        scope.end = tmpj;
    }else{
        scope.type = ScopeType::Multiplication;
        scope.start = k;
        scope.end = j;
        
    }

    
    
    // scope.auxOps = scopeAuxOp(scope, expression);
    return scope;
}

Scope MParser::scopeRational(int i, string expression){

    Scope scope;
    scope.type = ScopeType::Division;
    scope.appendOperator('/', i - 1, i + 1);

    int j = i + 1;
    int k = i - 1;

    bool forwards = true;
    bool backwards = true;

    while (true){
        if (forwards){
            if (isalpha(expression[j]) || isdigit(expression[j])){
                j = scopeTerm(j, expression).end;
            }else if (expression[j] == '('){
                j = findMatchingBracket(j, expression) + 1;
            }else if (expression[j] == '['){
                // int rootOperator = findMatchingBracket(j, expression) + 1;
                // j = scopeAuxOp(rootOperator, expression).end;
                j = findMatchingBracket(j, expression) + 2;
            }else if (expression[j] == '^'){
                // j = scopeAuxOp(j, expression).end;
                j = findMatchingBracket(j + 1, expression);
            }else{
                forwards = false;
            }
        }
        if (backwards){
            if (isalpha(expression[k]) || isdigit(expression[k])){
                k = scopeTerm(k, expression).start;
            }else if (expression[k] == ')'){
                k = findMatchingBracket(k, expression) - 1;
            }else if (expression[k] == '}'){
                // int exponentOperator = findMatchingBracket(k, expression) - 1;
                // k = scopeAuxOp(exponentOperator, expression).start;
                k = findMatchingBracket(k, expression) - 2;
            }else if (expression[k] == 'v'){
                // k = scopeAuxOp(k, expression).start;
                k = findMatchingBracket(k - 1, expression);
            }else{
                backwards = false;
            }
        }

        if (j >= expression.size()){
            forwards = false;
        }
        if (k < 0){
            backwards = false;
        }
        if (!forwards && !backwards){
            break;
        }
    }

    if (expression[k] == '-'){
        scope.sign = false;
    }
    
    
    scope.start = k;
    scope.end = j;
    // scope.auxOps = scopeAuxOp(scope, expression);
    return scope;

}

Scope MParser::scopeAuxOp(int i, string expression){
    Scope scope;

    int j = i + 1;
    int k = i - 1;

    if (expression[i] == '^'){
        scope.type = ScopeType::Exponent;
        scope.appendOperator('^', i - 1, i + 1);
        j = findMatchingBracket(j, expression) + 1;
        if (isalpha(expression[k]) || isdigit(expression[k])){
            k --;
        }else if (expression[k] == ')'){
            k = findMatchingBracket(k, expression) - 1;
        }else{
            // throw
        }
        
        // while(expression[j] == '^'){
        //     j = findMatchingBracket(j + 1, expression) + 1;
        // }
    }else if (expression[i] == 'v'){
        scope.type = ScopeType::Radical;
        scope.appendOperator('v', i - 1, i + 1);
        k = findMatchingBracket(k, expression) - 1;
        if (isalpha(expression[j]) || isdigit(expression[j])){
            j ++;
        }else if (expression[j] == '('){
            j = findMatchingBracket(j, expression) + 1;
        }else{
            // throw
        }
        // while(expression[k] == 'v'){
        //     k = findMatchingBracket(k - 1, expression) - 1;
        // }

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

    }else if ((isalpha(symbol) || isdigit(symbol)) && symbol != 'v'){

        return scopeTerm(i, expression);

    }else if (symbol == '/'){

        return scopeRational(i, expression);

    }else if (symbol == '^' || symbol  == 'v'){ // parse til escape char '|'

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

    string sanitised = sanitise(expression, "operation"); // remove negative sign of main operation, but not negative sign of operands
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
            operands.push_back(sanitise(newOperand, "operand"));
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

