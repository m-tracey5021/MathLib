#include "constantElement.h"

ConstantElement::ConstantElement(): Symbol(){}

ConstantElement::ConstantElement(int value): Symbol(value), value(value){}