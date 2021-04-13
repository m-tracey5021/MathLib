#include "auxOp.h"
#include "symbol.h"

AuxOp::AuxOp(){}

AuxOp::AuxOp(unique_ptr<Symbol>& root): root(move(root)){}

AuxOp::~AuxOp() = default;

void AuxOp::setRoot(unique_ptr<Symbol>& root){
    this->root = move(root);
}

unique_ptr<Symbol>& AuxOp::getRoot(){
    return root;
}

unique_ptr<AuxOp> AuxOp::copy(){}

string AuxOp::toString(){return "";}