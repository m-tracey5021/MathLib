#include "operation.h"

Operation::Operation(): Symbol(){}

Operation::Operation(char op): Symbol(op){}

Operation::Operation(char op, bool sign): Symbol(op, sign){}

Operation::Operation(char op, bool sign, vector<unique_ptr<Symbol>>& operands): Symbol(op, sign), operands(move(operands)){}

Operation::~Operation() = default;

// Operation::Operation(char op, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Symbol(op, auxOp), operands(move(operands)){}

// Operation::Operation(char op, bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Symbol(op, sign, auxOp), operands(move(operands)){}



int Operation::getValue(){return 0;}

void Operation::appendChild(unique_ptr<Symbol>& child){
    shared_ptr<Symbol> parent = shared_ptr<Symbol>(this);
    child->setParent(parent);
    operands.push_back(move(child));
}

// void Operation::appendChild(unique_ptr<Operation>& child){
//     shared_ptr<Symbol> parent = shared_ptr<Symbol>(this);
//     child->setParent(parent);
//     operands.push_back(move(child));
// }

unique_ptr<Symbol>& Operation::getNthChild(int n){
    return operands[n];
}

vector<unique_ptr<Symbol>>& Operation::getAllChildren(){
    return operands;
}

vector<unique_ptr<Symbol>> Operation::duplicateChildren(){
    vector<unique_ptr<Symbol>> duplicates;
    for (int i = 0; i < operands.size(); i ++){
        unique_ptr<Symbol> duplicate = operands[i]->copy();
        duplicates.push_back(move(duplicate));
    }
    return duplicates;
}

vector<unique_ptr<Symbol>> Operation::duplicateChildren(int start, int end){
    vector<unique_ptr<Symbol>> duplicates;
    for (int i = start; i < end; i ++){
        unique_ptr<Symbol> duplicate = operands[i]->copy();
        duplicates.push_back(move(duplicate));
    }
    return duplicates;
}

unique_ptr<Symbol>& Operation::expandExponent(){}

unique_ptr<Symbol>& Operation::expandAsExponent(unique_ptr<Symbol>& base){}

unique_ptr<Symbol> Operation::copy(){}

string Operation::toString(){return "";}

string Operation::toString(int depth, int offset){
    
    string str = "";
    int spaces = depth * offset;
    if (!sign){
        spaces -= 2;
    }
    for (int i = 0; i < spaces; i ++){
        str += ' ';
    }
    if (!sign){
        str += "-(";
        str += symbol;
        str += ')';
    }else{
        str += symbol;
    }
    
    depth ++;
    for (int i = 0; i < operands.size(); i ++){
        str += '\n';
        str += operands[i]->toString(depth, offset);
    }
    
    return str;


}

