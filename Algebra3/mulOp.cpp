#include "mulOp.h"
#include "expressionComponents.h"

Expression MulOp::add(SumOp& other){}

Expression MulOp::add(MulOp& other){}

Expression MulOp::add(DivOp& other){}

Expression MulOp::add(Exponent& other){}

Expression MulOp::add(Radical& other){}

Expression MulOp::add(Variable& other){}

Expression MulOp::add(Constant& other){}