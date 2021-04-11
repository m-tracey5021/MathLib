#include "operation.h"

Operation::Operation(): Symbol(){}

Operation::Operation(char op): Symbol(op){}

Operation::Operation(char op, bool sign): Symbol(op, sign){}

Operation::Operation(char op, bool sign, vector<unique_ptr<Symbol>>& operands): Symbol(op, sign), operands(move(operands)){}

Operation::Operation(char op, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Symbol(op, auxOp), operands(move(operands)){}

Operation::Operation(char op, bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Symbol(op, sign, auxOp), operands(move(operands)){}

void Operation::appendChild(unique_ptr<Symbol>& child){operands.push_back(move(child));}

void Operation::appendChild(Symbol* child){
    unique_ptr<Symbol> toAdd = unique_ptr<Symbol>(child);
    operands.push_back(move(toAdd));
}

unique_ptr<Symbol> Operation::copy(){}

string Operation::toString(){return "";}

