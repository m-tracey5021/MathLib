#include "operation.h"
#include "expressionComponents.h"

Operation::Operation(): Symbol(){}

Operation::Operation(char op): Symbol(op){}

Operation::Operation(char op, bool sign): Symbol(op, sign){}

Operation::Operation(char op, bool sign, vector<unique_ptr<Symbol>>& operands): Symbol(op, sign), operands(move(operands)){}

Operation::~Operation() = default;

// Operation::Operation(char op, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Symbol(op, auxOp), operands(move(operands)){}

// Operation::Operation(char op, bool sign, unique_ptr<AuxOp>& auxOp, vector<unique_ptr<Symbol>>& operands): Symbol(op, sign, auxOp), operands(move(operands)){}



int Operation::getValue(){return 0;}

bool Operation::isAtomic(){return false;}

void Operation::appendChild(unique_ptr<Symbol>& child){
    child->setIndex(operands.size());
    operands.push_back(move(child));
    return;
}

void Operation::appendChildren(vector<unique_ptr<Symbol>>& children){
    int currentSize = operands.size();
    for (int i = 0; i < children.size(); i ++){
        children[i]->setIndex(currentSize + i);
        operands.push_back(move(children[i]));
    }
    return;
}

void Operation::appendChildren(vector<unique_ptr<Symbol>>& children, int n){
    
    for (unique_ptr<Symbol>& child : children){
        child->setIndex(n);
        operands.insert(operands.begin() + n, move(child));
        n ++;
    }
    for (int i = n; i < operands.size(); i ++){
        operands[i]->setIndex(i);
    }
    return;
}

void Operation::replaceChild(unique_ptr<Symbol>& child, int n){
    for (int i = 0; i < operands.size(); i ++){
        if (i == n){
            operands[i] = move(child);
            child->setIndex(n);
        }
    }
    return;
}

void Operation::removeChild(unique_ptr<Symbol>& child){
    child->setIndex(-1);
    for (int i = 0; i < operands.size(); i ++){
        if (operands[i] == child){
            operands.erase(operands.begin() + i);
            return;
        }
    }
    return;
}

void Operation::removeChild(int n){
    operands[n]->setIndex(-1);
    operands.erase(operands.begin() + n);
    return;
}

unique_ptr<Symbol>& Operation::getChild(int n){
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

void Operation::expandExponent(Symbol* parent){}

void Operation::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){}

unique_ptr<Symbol> Operation::copy(){}

string Operation::toString(bool hasParent){return "";}

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

