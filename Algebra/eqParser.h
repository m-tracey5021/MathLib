#include "equation.h"
#include "equationComponents.h"
#include <ctype.h>
#include <string>
#include <utility>
#include <map>

using namespace std;

int* findSurroundingBrackets(string eq, int startPos, char bracketType);

bool parseForSign(string expStr, int index);

pair<TermBase*, int> parseTerm(string expStr, int startIndex, bool currenSign);

pair<RationalExpression*, int> parseRational(string expStr, int startIndex, bool currentSign);

pair<RadicalExpression*, int> parseRadical(string expStr, int startIndex, bool currentSign);

pair<Expression*, int> parseExpression(string expStr, int startIndex, bool currentSign);

Equation* parseEquation(string eqStr);

