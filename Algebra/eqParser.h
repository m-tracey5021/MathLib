#pragma once

#include "equation.h"
#include "EquationComponents/termBase.h"
#include "EquationComponents/constant.h"
#include "EquationComponents/variable.h"
#include "EquationComponents/termContainer.h"


using namespace std;

//int* findSurroundingBrackets(string eq, int startPos, char bracketType);

//bool parseForSign(string expStr, int i);

//int parseForCoefficient(string expStr, int& i);

TermContainer* parseExpression(string expStr, int& i);

Equation* parseEquation(string eqStr);

