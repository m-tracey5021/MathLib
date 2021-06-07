#include "mulOp.h"
#include "expressionComponents.h"

MulOp::MulOp(): Operation('*'){}

MulOp::MulOp(bool sign): Operation('*', sign){}

MulOp::MulOp(bool sign, vector<unique_ptr<Symbol>>& children): Operation('*', sign, children){}

MulOp::MulOp(bool sign, shared_ptr<Expression>& parentExpression): Operation('*', sign, parentExpression){}

MulOp::MulOp(bool sign, vector<unique_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('*', sign, children, parentExpression){}

unique_ptr<Symbol> MulOp::extractCoeff(){
    int coeffVal = 1;
    int i = 0;
    while (true){
        int val = children[i]->getValue();
        if (val > 0 && children[i]->isAtomic() && !children[i]->getIsTarget()){
            
            coeffVal = coeffVal * val;
            removeChild(i);
            if (i >= children.size()){
                break;
            }
            
        }else{
            i ++;
        }

    }
    unique_ptr<Symbol> coeff = make_unique<Constant>(coeffVal);
    return coeff;
}

int MulOp::getValue(){return 0;}

bool MulOp::isAtomicExponent(){return false;}

bool MulOp::isAtomicNumerator(){return true;} // eventually implement a toSum function, which turns multiplications into sums which are not atomic

void MulOp::replaceChild(unique_ptr<MulOp>& child, int n){
    vector<unique_ptr<Symbol>>& children = child->getChildren();
    for (unique_ptr<Symbol>& c : children){
        c->setParentExpression(parentExpression);
        children.push_back(move(c));
    }
    return;
}

void MulOp::expandExponent(Symbol* parent){
    for (int i = 0; i < children.size(); i ++){
        children[i]->expandExponent(this);
    }
    return;
}

void MulOp::expandAsExponent(Symbol& base, Symbol* parent, Symbol* grandparent){ // x^(2y) x = base 2y = operands y = duplicates
    
    for (int i = 0; i < children.size(); i ++){
        children[i]->expandExponent(this);
    }
    unique_ptr<Symbol> root = make_unique<MulOp>();
    unique_ptr<Symbol> coeff = extractCoeff();
    for (int i = 0; i < coeff->getValue(); i ++){
        unique_ptr<Symbol> op = make_unique<Exponent>();
        unique_ptr<Symbol> target = base.copy();
        unique_ptr<Symbol> exponent;
        if (children.size() == 1){
            exponent = children[0]->copy();
        }else{
            exponent = make_unique<MulOp>();
            for (int j = 0; j < children.size(); j ++){
                unique_ptr<Symbol> exponentOperand = children[j]->copy();
                exponent->appendChild(exponentOperand);
            }
        }
        target->setIsTarget(true);
        exponent->setIsExponent(true);
        op->appendChild(target);
        op->appendChild(exponent);
        root->appendChild(op);
    }
    // return root;   
    parentExpression->replaceNode(parent, root);
    
}

unique_ptr<Symbol> MulOp::copy(){

    unique_ptr<Symbol> copy = make_unique<MulOp>(sign);
    vector<unique_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        unique_ptr<Symbol> copied = children[i]->copy();
        copiedOperands.push_back(move(copied));
    }
    
    copy->setIndex(index);
    return copy;
}

string MulOp::toString(bool hasParent){
    string ret = "";
    for (int i = 0; i < children.size(); i ++){
        ret += children[i]->toString(true);
    }
    if (!sign){
        ret = '-' + ret;
    }
    if (isExponent){
        ret = '{' + ret + '}';
    }else if(isRadical){
        ret = '[' + ret + ']';
    }else if(isTarget){
        ret = '(' + ret + ')';
    }
    // if (parent != nullptr){
    //     ret = '(' + ret + ')';
    // }
    // if (auxOp != nullptr && includeAuxilliaries){
    //     ret = auxOp->toString(ret);
    // }
    return ret;
}

// string MulOp::toString(int& depth, int offset){
//     str += '\n';

//     int spaces = depth * offset;
//     for (int i = 0; i < spaces; i ++){
//         str += ' ';
//     }
//     if (!sign){
//         str += "-(*)";
//     }else{
//         str += '*';
//     }
//     depth ++;
//     for (int i = 0; i < operands.size(); i ++){
//         str += operands[i]->toString(str, depth, offset);
//     }
    
//     return str;

//     return "";
// }