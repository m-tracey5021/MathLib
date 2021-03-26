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

// Multiplication ::= (Constant *Variable) ?AuxillaryOperation

// Division ::= (Term '/' Term) ?AuxillaryOperation

// AuxillaryOperation ::= Root | Exponent

// Root ::= 'v' Expression EscapeCharacter

// Exponent ::= '^' Expression EscapeCharacter

// EscapeCharacter ::= '|'

// Constant ::= *('1' - '9') *('0' - '9')

// Variable ::= ('a' - 'z') / ('v')

// ===================


// enum class ParseState{

// };



MParser::MParser(){}

// unique_ptr<Symbol> MParser::buildSymbol(char c){
    
//     if (c == '+' || c == '-'){

//     }else if (c == '*'){

//     }else if (c == '/'){

//     }else if (c == '^'){
        
//     }else if (c == 'v'){

//     }else{
//         // throw error
//     }
// }

void MParser::parseExpression(string expression){

    // Expression expression = Expression();
    // Scope mainScope = findMainScope(expression);
    // char mainOp = mainScope.ops[0].first;
            
    // if (mainOp == '+'){

    //     unique_ptr<Symbol> op = make_unique<SumOp>(true);
    // }else if (mainOp == '-'){

    // }else if (mainOp == '/'){

    // }else if (mainOp == '*'){

    // }
}

void MParser::parseEquation(string equation){

}

void MParser::parseFunction(string function){

}

int MParser::findMatchingBracket(int i, string expression){
    int bracketStack = 0;
    if (expression[i] == '('){
        for (int j = i + 1; j < expression.size(); j ++){
            if (expression[j] == ')'){
                bracketStack ++;
            }else if (expression[j] == '('){
                bracketStack --;
            }
            if (bracketStack == 1){
                return j;
            }
        }
    }else if (expression[i] == ')'){
        for (int j = i - 1; j >= 0; j --){
            if (expression[j] == ')'){
                bracketStack --;
            }else if (expression[j] == '('){
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

vector<int> MParser::findSurroundingBrackets(int i, string expression){
    vector<int> brackets;

    int bracketStack;

    bool forwards = true;
    bool backwards = true;

    int j = i + 1;
    int k = i - 1;

    bracketStack = 0;
    while (forwards){
        if (j < expression.size()){
            if (expression[j] == '('){
                bracketStack ++;
            }else if (expression[j] == ')'){
                bracketStack --;
            }
            if (bracketStack == -1){
                forwards = false;
            }else{
                j ++;
            }
        }else{
            break;
        }
    }

    bracketStack = 0;
    while (backwards){
        if (k > -1){
            if (expression[k] == ')'){
                bracketStack ++;
            }else if (expression[k] == '('){
                bracketStack --;
            }
            if (bracketStack == -1){
                backwards = false;
            }else{
                k --;
            }
        }else{
            break;
        }
    }
    if (forwards & backwards){
        brackets = {-1, static_cast<int> (expression.size())};
    }else{
        brackets = {k, j};
    }
    return brackets;
}

// void MParser::appendOperator(Scope scope, int i, string expression, bool forwards){
//     pair<char, int> opWithinScope = {expression[i], i};
//     int currentSize = scope.ops.size();
//     int priorOp = scope.ops[currentSize - 1].second;
//     if (forwards)[

//     ]else{

//     }
// }

Scope MParser::scopeLowPriorityOp(int i, string expression){ // applies to + and -

    Scope scope;
    pair<char, int> mainOp = {expression[i], i};
    scope.ops.push_back(mainOp);

    int bracketStack;

    bool forwards = true;
    bool backwards = true;

    int j = i + 1;
    int k = i - 1;

    bracketStack = 0;
    while (forwards){
        if (j < expression.size()){
            if (expression[j] == '('){
                bracketStack ++;
            }else if (expression[j] == ')'){
                bracketStack --;
            }else if ((expression[j] == '+' || expression[j] == '-') && bracketStack == 0){
                pair<char, int> opWithinScope = {expression[j], j};
                scope.ops.push_back(opWithinScope);
            }
            if (bracketStack == -1){
                forwards = false;
            }else{
                j ++;
            }
        }else{
            break;
        }
    }

    bracketStack = 0;
    while (backwards){
        if (k > -1){
            if (expression[k] == ')'){
                bracketStack ++;
            }else if (expression[k] == '('){
                bracketStack --;
            }else if ((expression[k] == '+' || expression[k] == '-') && bracketStack == 0){
                pair<char, int> opWithinScope = {expression[k], k};
                scope.ops.push_back(opWithinScope);
            }
            if (bracketStack == -1){
                backwards = false;
            }else{
                k --;
            }
        }else{
            break;
        }
    }
    if (forwards & backwards){
        scope.start = -1;
        scope.end = static_cast<int> (expression.size());
    }else{
        scope.start = k;
        scope.end = j;
    }
    return scope;
}

Scope MParser::scopeHighPriorityOp(int i, string expression){ // applies to * and /
    
    //vector<int> scope;
    Scope scope;

    bool multiplication;
    if(expression[i] == '/'){
        multiplication = false;
        pair<char, int> op = {'/', i};
    }
    
    int j = i + 1;
    int k = i - 1;
    bool forwards = true;
    bool backwards = true;
    while (true){
        if (forwards){
            if (isalpha(expression[j]) || isdigit(expression[j])){
                // if(multiplication){

                // }
                j ++;
            }else if (expression[j] == '('){
                j = findMatchingBracket(j, expression) + 1;
            }else{
                forwards = false;
            }
        }
        if (backwards){
            if (isalpha(expression[k]) || isdigit(expression[k])){
                k --;
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
        if (!forwards & !backwards){
            break;
        }
    }
    pair<char, int> op;
    expression[i] == '/' ? op = {'/', i} : op = {'*', i}; 
    scope.ops.push_back(op);
    scope.start = k;
    scope.end = j;
    return scope;
}

Scope MParser::scopeAuxOp(int i, string expression){
    Scope scope;
    int j = i + 1;
    int k = i - 1;
    while(true){
        if (expression[j] == '|'){
            break;
        }else{
            j ++;
        }
    }
    if (expression[k] == ')'){
        k = findMatchingBracket(k, expression);
    }else if(isalpha(expression[k]) || isdigit(expression[k])){
        k = scopeHighPriorityOp(k, expression).end;
    }else{
        // throw error
    }
    pair<char, int> op = {expression[i], i};
    scope.ops.push_back(op);
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

        // vector<int> addOp = scopeLowPriorityOp(i, expression);
        // scope.start = addOp[0];
        // scope.end = addOp[1];
        // symbol == '+' ? scope.op = '+' : scope.op = '-';
        // return scope;
        return scopeLowPriorityOp(i, expression);

    }else if ((isalpha(symbol) || isdigit(symbol) || symbol == '/') && symbol != 'v'){

        // vector<int> mulOp = scopeHighPriorityOp(i, expression);
        // scope.start = mulOp[0];
        // scope.end = mulOp[1];
        // symbol == '/' ? scope.op = '/' : scope.op = '*';
        // return scope;
        return scopeHighPriorityOp(i, expression);

    }else if (symbol == '^' || symbol  == 'v'){ // parse til escape char '|'

        // vector<int> auxOp = scopeAuxOp(i, expression);
        // scope.start = auxOp[0];
        // scope.end = auxOp[1];
        // symbol == '^' ? scope.op = '^' : scope.op = 'v';
        // return scope;
        return scopeAuxOp(i, expression);

    }else{

        // throw error
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

vector<string> MParser::separateOperands(string expression){
    
    vector<string> operands;
    Scope scope = findMainScope(expression);

    for (int i = 0; i <= scope.ops.size(); i ++){
        int j;
        int k;
        if (i == 0){
            j = 0;
            k = scope.ops[i].second;
        }else if (i == scope.ops.size()){
            j = scope.ops[i - 1].second + 1;
            k = expression.size() - j;
        }else{
            j = scope.ops[i - 1].second + 1;
            k = scope.ops[i].second - j;
        }
        string newOperand = expression.substr(j, k);
        operands.push_back(newOperand);
    }
    return operands;
}

