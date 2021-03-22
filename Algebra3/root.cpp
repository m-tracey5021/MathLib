#include "root.h"

Root::Root(): AuxOp('v'){}

Root::Root(ExpressionTree& expression): AuxOp('v', expression){}