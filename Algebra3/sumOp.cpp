#include "sumOp.h"
#include "expressionComponents.h"

SumOp::SumOp(): Operation('+'){}

SumOp::SumOp(bool sign): Operation('+', sign){}

SumOp::SumOp(bool sign, vector<unique_ptr<Symbol>>& children): Operation('+', sign, children){}

SumOp::SumOp(bool sign, shared_ptr<Expression>& parentExpression): Operation('+', sign, parentExpression){}

SumOp::SumOp(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('+', sign, children, parentExpression){}



int SumOp::getValue(){return 0;}

bool SumOp::isAtomicExponent(){return false;}

bool SumOp::isAtomicNumerator(){return false;}

void SumOp::replaceChild(unique_ptr<SumOp>& child, int n){
    vector<unique_ptr<Symbol>>& children = child->getChildren();
    for (unique_ptr<Symbol>& c : children){
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
    unique_ptr<Symbol> root = make_unique<MulOp>();
    for (int i = 0; i < children.size(); i ++){
        unique_ptr<Symbol> op = make_unique<Exponent>();
        unique_ptr<Symbol> target = base.copy();
        unique_ptr<Symbol> exponent = children[i]->copy();
        target->setIsTarget(true);
        exponent->setIsExponent(true);
        op->appendChild(target);
        op->appendChild(exponent);
        root->appendChild(root);
    }
    // return root;
    parentExpression->replaceNode(parent, root);
}

unique_ptr<Symbol> SumOp::copy(){
    unique_ptr<Symbol> copy = make_unique<SumOp>(sign);
    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        unique_ptr<Symbol> copied = children[i]->copy();
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