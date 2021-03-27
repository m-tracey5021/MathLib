#include "mParser.h"

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

unique_ptr<AuxOp> MParser::buildAuxOperation(char c){
    if (c == '^'){
        unique_ptr<AuxOp> exponent = make_unique<AuxOp>();
    }else if (c == 'v'){
        unique_ptr<AuxOp> root = make_unique<Root>();
    }else if (c == 'f'){
        unique_ptr<AuxOp> function = make_unique<AuxOp>();
    }else{
        // throw
    }
}

void MParser::parseExpression(unique_ptr<Symbol>& parentSymbol, string expression){

    Scope mainScope = findMainScope(expression);

    if (mainScope.type == ScopeType::Atomic){
        
    }else{

        unique_ptr<Symbol> mainOp = buildOperation(mainScope.ops[0].op);
        parentSymbol->appendChild(mainOp);

        vector<string> operands = separateOperands(mainScope, expression);    

        for (string operand : operands){
            parseExpression(mainOp, operand);
        }
    }  
}

void MParser::parseEquation(string equation){

}

void MParser::parseFunction(string function){

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
            if (bracketStack == 1){
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
            if (expression[j] == '('){
                rhsBracketStack ++;
            }else if (expression[j] == ')'){
                rhsBracketStack --;
            }else if ((expression[j] == '+' || expression[j] == '-') && rhsBracketStack == 0){
                scope.appendOperator(expression[j], j - 1, j + 1);
            }
            if (rhsBracketStack == -1){
                forwards = false;
            }else{
                j ++;
            }
        }
        if (backwards){
            if (expression[k] == ')'){
                lhsBracketStack ++;
            }else if (expression[k] == '('){
                lhsBracketStack --;
            }else if ((expression[k] == '+' || expression[k] == '-') && lhsBracketStack == 0){
                scope.appendOperator(expression[k], k - 1, k + 1);
            }
            if (lhsBracketStack == -1){
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
    return scope;
}

Scope MParser::scopeTerm(int i, string expression){ // applies to * and atoms
    
    Scope scope;

    bool isAtomic;
    bool isConstant = true;

    int j = i;
    int k = i;
    
    bool forwards = true;
    bool backwards = true;
    while (true){
        if (forwards){
            if (isalpha(expression[j])){
                if (j != i){
                    scope.appendOperator('*', j - 1, j);
                }
                isConstant = false;
                j ++;
            }else if (isdigit(expression[j])){
                j = scopeConstant(j, expression).end;
            }else if (expression[j] == '('){
                scope.appendOperator('*', j - 1, j);
                isConstant = false;
                j = findMatchingBracket(j, expression) + 1;
            }else{
                forwards = false;
            }
        }
        if (backwards){
            if (isalpha(expression[k])){
                if (k != i){
                    scope.appendOperator('*', k, k + 1);
                }
                isConstant = false;
                k --;
            }else if (isdigit(expression[k])){
                k = scopeConstant(k, expression).start;
            }else if (expression[k] == ')'){
                scope.appendOperator('*', k, k + 1);
                isConstant = false;
                k = findMatchingBracket(k, expression) - 1;
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

    if ((j - k) == 1 || isConstant){
        scope.type = ScopeType::Atomic;
    }else{
        scope.type = ScopeType::Multiplication;
    }

    scope.start = k;
    scope.end = j;
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
            }else{
                forwards = false;
            }
        }
        if (backwards){
            if (isalpha(expression[k]) || isdigit(expression[k])){
                k = scopeTerm(k, expression).start;
            }else if (expression[k] == ')'){
                k = findMatchingBracket(k, expression) - 1;
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
    return scope;

}

Scope MParser::scopeAuxOp(int i, string expression){
    Scope scope;

    int j = i + 1;
    int k = i - 1;

    if (expression[i] == '^'){
        scope.type = ScopeType::Exponent;
        j = findMatchingBracket(j, expression) + 1;
        if (isalpha(expression[k]) || isdigit(expression[k])){
            k --;
        }else if (expression[k] == ')'){
            k = findMatchingBracket(k, expression) - 1;
        }else{
            // throw
        }
    }else if (expression[i] == 'v'){
        scope.type = ScopeType::Radical;
        k = findMatchingBracket(k, expression) - 1;
        if (isalpha(expression[j]) || isdigit(expression[j])){
            j ++;
        }else if (expression[j] == '('){
            j = findMatchingBracket(j, expression) + 1;
        }else{
            // throw
        }

    }
    scope.appendOperator(expression[i], i - 1, i + 1);
    scope.start = k;
    scope.end = j;
    return scope;
}


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
            }else{
                forwards = false;
            }
        }

        if (backwards){
            if(isdigit(expression[k])){
                k --;
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
        operands.push_back(newOperand);
    }
    return operands;
}

