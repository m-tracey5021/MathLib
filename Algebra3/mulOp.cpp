#include "mulOp.h"
#include "expressionComponents.h"
#include "Visitors/appendToMulOp.h"
#include "Visitors/sanitiseMulOp.h"


MulOp::MulOp(): Operation('*'){}

MulOp::MulOp(bool sign): Operation('*', sign){}

MulOp::MulOp(bool sign, vector<shared_ptr<Symbol>>& children): Operation('*', sign, children){}

MulOp::MulOp(bool sign, shared_ptr<Expression>& parentExpression): Operation('*', sign, parentExpression){}

MulOp::MulOp(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('*', sign, children, parentExpression){}

unique_ptr<Symbol> MulOp::extractCoeff(){
    int coeffVal = 1;
    int i = 0;
    while (true){
        
        if (children[i]->getValue() && children[i]->isAtomic() && !children[i]->getIsTarget()){
            int val = *children[i]->getValue();
            coeffVal = coeffVal * val;
            // removeChild(i);
            parentExpression->removeNode(children[i].get());
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

void MulOp::accept(Visitor* visitor){
    visitor->Visit(this);
}

bool MulOp::isAtomicExponent(){return false;}

bool MulOp::isAtomicNumerator(){return true;} // eventually implement a toSum function, which turns multiplications into sums which are not atomic

bool MulOp::isEqual(Symbol* other){}

// void MulOp::appendChild(shared_ptr<Symbol>& child){
//     unique_ptr<AppendToMulOp> append = make_unique<AppendToMulOp>(*this, child);
//     child->accept(append.get());
// }

void MulOp::evaluateConstants(){
    int total = 1;
    bool totalSign = true;
    bool change = false;
    for (int i = 0; i < children.size(); i ++){
        optional<int> result = children[i]->getValue();
        if (result){
            evaluateSingleConstant(result, i, total, totalSign);
            change = true;
        }else{
            children[i]->evaluateConstants();
            optional<int> newResult = children[i]->getValue();
            if (newResult){
                evaluateSingleConstant(newResult, i, total, totalSign);
                change = true;
            }
        }
    }
    // create new constant from total
    if (change){
        shared_ptr<Symbol> multiplied = make_shared<Constant>(totalSign, total);
        if (children.size() == 0){
            // replace this with new constant
            parentExpression->replaceNode(this, multiplied);
        }else{
            appendChild(multiplied);
        }
    }
}

void MulOp::evaluateSingleConstant(optional<int>& result, int& index, int& total, bool& totalSign ){
    int val = *result;
    total *= val;
    if (children[index]->getSign()){
        if (!totalSign){
            totalSign = true;
        }
    }else{
        totalSign = false;
    }
    parentExpression->removeNode(children[index].get());
    index --;
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
    shared_ptr<Symbol> root = make_shared<MulOp>();
    shared_ptr<Symbol> coeff = extractCoeff();
    for (int i = 0; i < coeff->getValue(); i ++){
        shared_ptr<Symbol> op = make_shared<Exponent>();
        shared_ptr<Symbol> target = base.copy();
        shared_ptr<Symbol> exponent;
        if (children.size() == 0){
            if (coeff.get() != nullptr){
                
            }
        }else if (children.size() == 1){
            exponent = children[0]->copy();
        }else{
            exponent = make_shared<MulOp>();
            for (int j = 0; j < children.size(); j ++){
                shared_ptr<Symbol> exponentOperand = children[j]->copy();
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

shared_ptr<Symbol> MulOp::sanitise(){
    unique_ptr<SanitiseMulOp> sanitise = make_unique<SanitiseMulOp>();
    for (int i = 0; i < children.size(); i ++){
        children[i]->accept(sanitise.get());
        if (sanitise->multiplyValue){

        }
    }
}

shared_ptr<Symbol> MulOp::copy(){

    shared_ptr<Symbol> copy = make_shared<MulOp>(sign);
    vector<shared_ptr<Symbol>> copiedOperands;
    for (int i = 0; i < children.size(); i ++){
        shared_ptr<Symbol> copied = children[i]->copy();
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