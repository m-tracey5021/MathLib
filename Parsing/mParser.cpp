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

unique_ptr<Symbol> MParser::buildSymbol(ScopeType type, string expression){
    if (type == ScopeType::Atomic){
        if (expression.size() == 1 && isalpha(expression[0])){
            unique_ptr<Variable> variable = make_unique<Variable>(expression[0]);
            return variable;
        }else{
            int num = std::stoi(expression);
            unique_ptr<Constant> constant = make_unique<Constant>(num);
            return constant;
        }
    }else if (type == ScopeType::Summation){
        unique_ptr<SumOp> sumOp = make_unique<SumOp>();
        return sumOp;
    }else if (type == ScopeType::Multiplication){
        unique_ptr<MulOp> mulOp = make_unique<MulOp>();
        return mulOp;
    }else if (type == ScopeType::Division){
        unique_ptr<DivOp> divOp = make_unique<DivOp>();
        return divOp;
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

unique_ptr<AuxOp> MParser::buildAuxOperation(char c, string expression){
    unique_ptr<Symbol> root = unique_ptr<Symbol>();
    parseExpression(root, expression);
    if (c == '^'){
        unique_ptr<AuxOp> exponent = make_unique<Exponent>(root);
        return exponent;
    }else if (c == 'v'){
        unique_ptr<AuxOp> radical = make_unique<Radical>(root);
        return radical;
    }else if (c == 'f'){
        unique_ptr<AuxOp> function = make_unique<Function>(root);
        return function;
    }else{
        // throw
    }
}

unique_ptr<AuxOp> MParser::buildAuxOperationChain(vector<AuxOpInfo>& auxillaries, string expression){

    // make sure that somewhere further up the chain there is a 
    // check that makes it impossible to both take a radical and 
    // an exponent at the same time

    shared_ptr<AuxOp> rootAuxOp;

    shared_ptr<AuxOp> currentAuxOp;
    shared_ptr<AuxOp> previousAuxOp;

    for (AuxOpInfo auxillary : auxillaries){
        currentAuxOp = move(buildAuxOperation(auxillary.op, expression.substr(auxillary.start + 1, auxillary.end - (auxillary.start + 1))));

        if (!rootAuxOp){
            // root = current;
            // previous = current;
            rootAuxOp = currentAuxOp;
            previousAuxOp = currentAuxOp;
        }else{
            // rootSymbol& = previous->getRoot()
            // rootSymbol->appendAuxillary(current);
            // previous = current;
            unique_ptr<Symbol>& rootSymbol = previousAuxOp->getRoot();
            unique_ptr<AuxOp> copiedCurrent = currentAuxOp->copy();
            rootSymbol->appendAuxillary(copiedCurrent);
            previousAuxOp = currentAuxOp;

        }
    }
    if (rootAuxOp != nullptr){
        unique_ptr<AuxOp> copiedRoot = rootAuxOp->copy();
        return copiedRoot;
    }else{
        unique_ptr<AuxOp> null = unique_ptr<AuxOp>();
        return null;
        // return nullptr kinda deal
    }
    
}

void MParser::parseExpression(string expression){
    parseTree = Expression();
    unique_ptr<Symbol> root = unique_ptr<Symbol>();
    parseExpression(root, expression);
    parseTree.setRoot(root);
}

void MParser::parseExpression(unique_ptr<Symbol>& parent, string expression){    

    Scope mainScope = findMainScope(expression);

    unique_ptr<Symbol> child;
    // unique_ptr<AuxOp> auxOp = buildAuxOperationChain(mainScope.auxOps, expression);

    bool emptyTree;
    parent == nullptr ? emptyTree = true : emptyTree = false;

    if (mainScope.type == ScopeType::Atomic){
        // child = buildAtom(expression.substr(mainScope.start + 1, mainScope.end - mainScope.start - 1));
        // child->appendAuxillary(auxOp);

        string atom = expression.substr(mainScope.start + 1, mainScope.end - mainScope.start - 1);
        child = buildSymbol(mainScope.type, atom);

        if (emptyTree){
            parent = move(child);
        }else{
            parent->appendChild(child);
        }

        return;
        
    }else if (mainScope.type == ScopeType::Exponent || mainScope.type == ScopeType::Radical) {

        pair<string, vector<string>> auxillaryPair = separateAuxillaries(mainScope, expression);

        Scope targetScope = findMainScope(auxillaryPair.first);

        child = buildSymbol(targetScope.type, auxillaryPair.first);

        parseExpression(parent, auxillaryPair.first);

        if (emptyTree){
            parent = move(child);
        }else{
            parent->appendChild(child);
        }

    }else{

        // child = buildOperation(mainScope.type);
        // child->appendAuxillary(auxOp);

        child = buildSymbol(mainScope.type, expression);

        vector<string> operands = separateOperands(mainScope, expression);
        // vector<string> auxillaries = separateAuxillaries(mainScope, expression);  

        // for (string auxillary : auxillaries){
            
        // }

        for (string operand : operands){
            parseExpression(child, operand);
        }



        if (emptyTree){
            parent = move(child);
        }else{
            parent->appendChild(child);
        }
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
    scope.appendOperator(expression[i], i - 1, i + 1);

    bool forwards = true;
    bool backwards = true;

    int j = i + 1;
    int k = i - 1;

    int lhsBracketStack = 0;
    int rhsBracketStack = 0;

    while (true){
        if (forwards){
            if (expression[j] == '+' || expression[j] == '-'){
                scope.appendOperator(expression[j], j - 1, j + 1);
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
            if (expression[k] == '+' || expression[k] == '-'){
                scope.appendOperator(expression[k], k - 1, k + 1);
                k --;
            }else if (expression[k] == ')' || 
                        expression[k] == '}' || 
                        expression[k] == ']'){
                k = findMatchingBracket(k, expression) - 1;
            }else if (expression[k] == '(' || 
                        expression[k] == '{' || 
                        expression[k] == '['){
                backwards = false;
            }else{
                k --;
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
    
    bool forwards = true;
    bool backwards = true;
    while (true){
        if (forwards){
            if (isalpha(expression[j]) && expression[j] != 'v'){
                if (j != i){
                    scope.appendOperator('*', j - 1, j);
                    operandCount ++;
                }
                j ++;
            }else if (isdigit(expression[j])){
                j = scopeConstant(j, expression).end;
                // operandCount ++;
            }else if (expression[j] == '('){
                scope.appendOperator('*', j - 1, j);
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
                if (expression[j] == '('){
                    j = findMatchingBracket(j, expression) + 1;
                    operandCount ++;
                }
            }else if (expression[j] == '^'){

                int tmp = findMatchingBracket(j + 1, expression);
                if (tmp + 1 > expression.size() || isClosingBracket(expression[tmp + 1])){
                    forwards = false;
                }else{
                    j = tmp + 1;
                }

                // vector<AuxOpInfo> auxOps = scopeAuxOp(j, expression);
                // int terminatingIndex = auxOps.back().end;
                // if (terminatingIndex + 1 >= expression.size() || isClosingBracket(expression[terminatingIndex])){
                //     forwards = false;
                //     scope.auxOps = auxOps;
                // }else{
                //     j = terminatingIndex;
                // }
            }else{
                forwards = false;
            }
        }
        if (backwards){
            if (isalpha(expression[k]) && expression[k] != 'v'){
                if (k != i){
                    scope.appendOperator('*', k, k + 1);
                    operandCount ++;
                }
                k --;
            }else if (isdigit(expression[k])){
                k = scopeConstant(k, expression).start;
                // operandCount ++;
            }else if (expression[k] == ')'){
                scope.appendOperator('*', k, k + 1);
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
                if (expression[k] == ')'){
                    k = findMatchingBracket(k, expression) - 1;
                    operandCount ++;
                }
            }else if (expression[k] == 'v'){

                int tmp = findMatchingBracket(k - 1, expression);
                if (tmp - 1 < 0 || isOpeningBracket(expression[tmp - 1])){
                    forwards = false;
                }else{
                    k = tmp - 1;
                }

                // vector<AuxOpInfo> auxOps = scopeAuxOp(k, expression);
                // int terminatingIndex = auxOps.back().start;
                // if (terminatingIndex - 1 < 0 || isOpeningBracket(expression[terminatingIndex])){
                //     backwards = false;
                //     scope.auxOps = auxOps;
                // }else{
                //     k = terminatingIndex;
                // }
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

    if (operandCount == 1){
        scope.type = ScopeType::Atomic;
    }else{
        scope.type = ScopeType::Multiplication;
        
    }

    
    scope.start = k;
    scope.end = j;
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
        while(expression[j] == '^'){
            scope.appendOperator('^', j - 1, j + 1);
            j = findMatchingBracket(j + 1, expression) + 1;
        }
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
        while(expression[k] == 'v'){
            scope.appendOperator('v', k - 1, k + 1);
            k = findMatchingBracket(k - 1, expression) - 1;
        }

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

    if (scope.type == ScopeType::Atomic){
        operands.push_back(expression);
        return operands;
    }else{
        for (int i = 0; i <= scope.ops.size(); i ++){
            int j;
            int k;
            if (i == 0){
                j = 0;
                k = scope.ops[i].between.first + 1;
            }else if (i == scope.ops.size()){
                j = scope.ops[i - 1].between.second;
                k = expression.size() - j;
            }else{
                j = scope.ops[i - 1].between.second;
                k = scope.ops[i].between.first + 1 - j;
            }
            
            string newOperand = expression.substr(j, k);
            if (newOperand[0] == '('){
                j ++;
                newOperand = expression.substr(j, k);
            }
            if (newOperand[newOperand.size() - 1] == ')'){
                k --;
                newOperand = expression.substr(j, k);
            }
            operands.push_back(newOperand);
        }
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

