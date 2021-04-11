#include "symbol.h"

Symbol::Symbol(){}

Symbol::Symbol(char symbol): symbol(symbol), sign(true){}

Symbol::Symbol(char symbol, bool sign): symbol(symbol), sign(sign){}

Symbol::Symbol(char symbol, unique_ptr<AuxOp>& auxOp): symbol(symbol), sign(true), auxOp(move(auxOp)){}

Symbol::Symbol(char symbol, bool sign, unique_ptr<AuxOp>& auxOp): symbol(symbol), sign(sign), auxOp(move(auxOp)){}

Symbol::~Symbol() = default;

void Symbol::appendChild(unique_ptr<Symbol>& child){}

unique_ptr<Symbol> Symbol::copy(){}

string Symbol::toString(){return "";}