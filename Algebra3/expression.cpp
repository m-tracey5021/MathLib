#include "expression.h"

Expression::Expression(){}

Expression::Expression(unique_ptr<Symbol>& symbol): root(move(symbol)){} 

unique_ptr<Symbol> Expression::getRoot(){return move(root);}

void Expression::setRoot(unique_ptr<Symbol>& symbol){
    root = move(symbol);
}

void Expression::setRoot(unique_ptr<Operation>& symbol){
    root = move(symbol);
}

void Expression::setRoot(Symbol* symbol){
    root = unique_ptr<Symbol>(symbol);
}

Expression Expression::expandExponents(){
    unique_ptr<Symbol> copy = root->copy();
    copy->expandExponent(nullptr);
    Expression expanded = Expression(copy);
    return expanded;
}

string Expression::toString(){
    return root->toString(false);
}

string Expression::toString(int offset){
    return root->toString(1, offset);
}