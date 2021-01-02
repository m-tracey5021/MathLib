#pragma once

#include "equation.h"
#include "equationComponents.h"

using namespace std;

enum class ParseState;

TermBase* parseExpression(string expStr, ParseState state, int& i);

TermBase* parseExpression(string expStr);

Equation* parseEquation(string eqStr);

