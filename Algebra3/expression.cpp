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

void Expression::expandExponents(){
    root = move(root->expandExponent());
}

string Expression::toString(){
    return root->toString();
}

string Expression::toString(int offset){
    return root->toString(1, offset);
}