#pragma once

#include "equation.h"
#include "equationComponents.h"

using namespace std;

TermBase* parseExpression(string expStr, bool expSign, int& i);

TermBase* parseExpression(string expStr);

Equation* parseEquation(string eqStr);

