#include "sumOp.h"
#include "expressionComponents.h"

SumOp::SumOp(): Operation('+'){}

SumOp::SumOp(bool sign): Operation('+', sign){}

SumOp::SumOp(bool sign, vector<shared_ptr<Symbol>>& children): Operation('+', sign, children){}

SumOp::SumOp(bool sign, shared_ptr<Expression>& parentExpression): Operation('+', sign, parentExpression){}

SumOp::SumOp(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('+', sign, children, parentExpression){}


void SumOp::accept(Visitor* visitor){
    visitor->Visit(this);
}

int SumOp::getValue(){return 0;}

bool SumOp::isAtomicExponent(){return false;}

bool SumOp::isAtomicNumerator(){return false;}

void SumOp::appendChild(shared_ptr<Symbol>& child){
    child->setIndex(children.size());
    child->setParentExpression(parentExpression);
    children.push_back(move(child));
}

void SumOp::appendToParent(SumOp* parent){
    
}

void SumOp::appendToParent(MulOp* parent){
    
}

void SumOp::appendToParent(DivOp* parent){
    
}

void SumOp::appendToParent(Exponent* parent){
    
}

void SumOp::appendToParent(Radical* parent){
    
}

void SumOp::appendToParent(Constant* parent){
    
}

void SumOp::appendToParent(Variable* parent){
    
}

void SumOp::replaceChild(shared_ptr<SumOp>& child, int n){
    vector<shared_ptr<Symbol>>& children = child->getChildren();
    for (shared_ptr<Symbol>& c : children){
        c->setParentExpression(parentExpression);
        children.push_back(move(c));
    }
    return;
}

void SumOp::expandExponent(Symbol* parent){
    for (int i = 0; i < children.size(); i ++){
        children[i]->expandExponent(this);
    }
    return;
}

void SumOp::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){
    
    for (int i = 0; i < children.size(); i ++){
        children[i]->expandExponent(this);
    }
    shared_ptr<Symbol> root = make_shared<MulOp>();
    for (int i = 0; i < children.size(); i ++){
        shared_ptr<Symbol> op = make_shared<Exponent>();
        shared_ptr<Symbol> target = base.copy();
        shared_ptr<Symbol> exponent = children[i]->copy();
        target->setIsTarget(true);
        exponent->setIsExponent(true);
        op->appendChild(target);
        op->appendChild(exponent);
        root->appendChild(root);
    }
    // return root;
    parentExpression->replaceNode(parent, root);
}

shared_ptr<Symbol> SumOp::copy(){
    shared_ptr<Symbol> copy = make_shared<SumOp>(sign);
    vector<shared_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        shared_ptr<Symbol> copied = children[i]->copy();
        // copied->setParent(copy);
        copiedOperands.push_back(move(copied));
    }
    
    copy->setIndex(index);
    return copy;
}

string SumOp::toString(bool hasParent){
    string ret = "";
    for (int i = 0; i < children.size(); i ++){
        if (i != 0){
            if (children[i]->getSign()){
                ret += '+' + children[i]->toString(true);
            }else{
                ret += children[i]->toString(true);
            }
            
        }else{
            ret += children[i]->toString(true);
        }
    }
    if (!sign){
        ret = "-(" + ret + ')';
    }
    // }else{
    //     if (hasParent && !isExponent && !isRadical){
    //         ret = '(' + ret + ')';
    //     }
    // }
    if (isExponent){
        ret = '{' + ret + '}';
    }else if(isRadical){
        ret = '[' + ret + ']';
    }else if (isTarget){
        ret = '(' + ret + ')';

    }else{
        if (hasParent){
            ret = '(' + ret + ')';
        }
    }

    // if (auxOp != nullptr && includeAuxilliaries){
    //     ret = auxOp->toString(ret);
    // }
    return ret;
}

// string SumOp::toString(int& depth, int offset){
//     str += '\n';

//     int spaces = depth * offset;
//     for (int i = 0; i < spaces; i ++){
//         str += ' ';
//     }
//     if (!sign){
//         str += "-(+)";
//     }else{
//         str += '+';
//     }
//     depth ++;
//     for (int i = 0; i < operands.size(); i ++){
//         str += operands[i]->toString(str, depth, offset);
//     }
    
//     return str;
//     return "";

// }