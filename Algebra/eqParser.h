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

Polynomial* parsePolynomial(string expStr);

Equation* parseEquation(string eqStr);

