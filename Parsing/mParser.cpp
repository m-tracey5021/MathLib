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

unique_ptr<Symbol> MParser::buildSymbol(char c){
    if (c == '+' | c == '-'){
        unique_ptr<Operation> op = unique_ptr<AddOp>(new AddOp());
        return op;
    }else if (c == '*'){

    }else if (c == '/'){

    }else if (c == '^'){
        
    }else if (c == 'v'){

    }else{
        // throw error
    }
}

void MParser::parseExpression(string expression){

    Scope largestScope;
    largestScope.start = 0;
    largestScope.end = 0;
    vector<Scope> scopes;
    int i = 0;

    while (true){

        Scope ithScope = findScope(i, expression);
        scopes.push_back(ithScope);
        i = ithScope.end;

        int ithScopeSize = ithScope.end - ithScope.start;
        int largestScopeSize = largestScope.end - largestScope.start;

        if (ithScopeSize > largestScopeSize){
            largestScope = ithScope;
        }
        if (i >= expression.size()){
            break;
        }
    }

    parseTree = ExpressionTree();
    if (largestScope.op == '+' | largestScope.op == '-' | largestScope.op == '*'){

    }else if (largestScope.op == '/'){

    }else{

    }


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

vector<int> MParser::findSurroundingBrackets(int i, string expression, vector<pair<char, vector<int>>>& toCount){
    vector<int> brackets;

    int bracketStack;

    bool forwards = true;
    bool backwards = true;

    int j = i;
    int k = i;

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

vector<int> MParser::scopeLowPriorityOp(int i, string expression){

    Scope scope;

    int bracketStack;

    bool forwards = true;
    bool backwards = true;

    int j = i;
    int k = i;

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
        scope.start = -1;
        scope.end = static_cast<int> (expression.size());
    }else{
        scope.start = k;
        scope.end = j;
    }
}

vector<int> MParser::scopeHighPriorityOp(int i, string expression){
    vector<int> scope;
    int j = i + 1;
    int k = i - 1;
    bool forwards = true;
    bool backwards = true;
    while (true){
        if (forwards){
            if (isalpha(expression[j]) | isdigit(expression[j])){
                j ++;
            }else if (expression[j] == '('){
                j = findMatchingBracket(j, expression) + 1;
            }else{
                forwards = false;
            }
        }
        if (backwards){
            if (isalpha(expression[k]) | isdigit(expression[k])){
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
        if (k <= 0){
            backwards = false;
        }
        if (!forwards & !backwards){
            break;
        }
    }
    scope = {k, j};
    return scope;
}

// vector<int> MParser::scopeOfDivOp(int i, string expression){
//     vector<int> scope;
//     int j = i + 1;
//     int k = i - 1;
//     if (expression[j] == '('){
//         j = findMatchingBracket(j, expression);
//     }else if (isalpha(expression[j]) | isdigit(expression[j])){
//         j = scopeOfMulOp(j, expression)[1];
//     }else{
//         // throw error
//     } 
//     if (expression[k] == ')'){
//         k = findMatchingBracket(k, expression);
//     }else if (isalpha(expression[k]) | isdigit(expression[k])){
//         k = scopeOfMulOp(k, expression)[0];
//     }else{
//         // throw error
//     }
//     scope = {k, j};
//     return scope;
    
// }

vector<int> MParser::scopeAuxOp(int i, string expression){
    vector<int> scope;
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
    }else if(isalpha(expression[k]) | isdigit(expression[k])){
        k = scopeHighPriorityOp(k, expression)[0];
    }else{
        // throw error
    }
    scope = {k, j};
    return scope;
}

// if given character, then finds the extent of the multiplication, if it only consists of one char
// then it is not a multiplication, it is atomic, if given an operator, either + or /, finds the 
// operands of the operator, if given a ( finds the closing bracker, and vice versa

Scope MParser::findScope(int i, string expression){ 
    Scope scope;
    char symbol = expression[i];
    if (symbol == '+' | symbol == '-'){

        vector<int> addOp = scopeLowPriorityOp(i, expression);
        scope.start = addOp[0];
        scope.end = addOp[1];
        symbol == '+' ? scope.op = '+' : scope.op = '-';
        return scope;

    }else if ((isalpha(symbol) | isdigit(symbol) | symbol == '/') & symbol != 'v'){

        vector<int> mulOp = scopeHighPriorityOp(i, expression);
        scope.start = mulOp[0];
        scope.end = mulOp[1];
        symbol == '/' ? scope.op = '/' : scope.op = '*';
        return scope;

    // }else if (symbol == '/'){

    //     vector<int> divOp = scopeOfMulOp(i, expression);
    //     scope.start = divOp[0];
    //     scope.end = divOp[1];
    //     scope.op = '/'; 
    //     return scope;

    }else if (symbol == '^' | symbol  == 'v'){ // parse til escape char '|'

        vector<int> auxOp = scopeAuxOp(i, expression);
        scope.start = auxOp[0];
        scope.end = auxOp[1];
        symbol == '^' ? scope.op = '^' : scope.op = 'v';
        return scope;

    }else{

        // throw error

    }
}

