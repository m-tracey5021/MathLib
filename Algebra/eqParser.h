#include "equation.h"
#include "equationComponents.h"
#include <ctype.h>
#include <string>

using namespace std;

//int* findSurroundingBrackets(string eq, int startPos, char bracketType);

//bool parseForSign(string expStr, int i);

//int parseForCoefficient(string expStr, int& i);

TermContainer* parseExpression(string expStr, int& i);

Equation* parseEquation(string eqStr);

