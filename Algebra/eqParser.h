#include "equation.h"
#include "expression.h"
#include <string>

using namespace std;

int* findSurroundingBrackets(string eq, int startPos);

Equation* parseEquation(string eqStr);

Expression* parseExpression(string expStr);