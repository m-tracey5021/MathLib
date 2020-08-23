#include "equation.h"
#include "equationComponents.h"
#include <ctype.h>
#include <string>
#include <utility>
#include <map>

using namespace std;

int* findSurroundingBrackets(string eq, int startPos);

Term* parseComplexTerm(string termStr);

Term* parseRationalExpression(string termStr);

bool parseForSign(string expStr, int index);

pair<Term*, int> parseTerm(string expStr, int startIndex, bool currenSign);

Expression* parseExpression(string expStr);

Equation* parseEquation(string eqStr);

