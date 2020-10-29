#pragma once

#include "equation.h"
#include "equationComponents.h"

using namespace std;

TermContainer* parseExpression(string expStr, int& i);

Equation* parseEquation(string eqStr);

