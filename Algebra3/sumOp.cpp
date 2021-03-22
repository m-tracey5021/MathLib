#include "sumOp.h"

AddOp::AddOp(): Operation('+'), sign('+'){}

AddOp::AddOp(char sign): Operation(sign), sign(sign){}