#include "sumOp.h"
#include "expressionComponents.h"
#include "Visitors/appendToSumOp.h"
#include "Visitors/equalTo.h"

SumOp::SumOp(): Operation('+'){}

SumOp::SumOp(bool sign): Operation('+', sign){}

SumOp::SumOp(bool sign, vector<shared_ptr<Symbol>>& children): Operation('+', sign, children){}

SumOp::SumOp(bool sign, shared_ptr<Expression>& parentExpression): Operation('+', sign, parentExpression){}

SumOp::SumOp(bool sign, vector<shared_ptr<Symbol>>& children, shared_ptr<Expression>& parentExpression): Operation('+', sign, children, parentExpression){}


void SumOp::accept(Visitor* visitor){
    visitor->Visit(this);
}

bool SumOp::isAtomicExponent(){return false;}

bool SumOp::isAtomicNumerator(){return false;}

bool SumOp::isEqual(Symbol* other){
    shared_ptr<EqualToSum> equal = make_shared<EqualToSum>(*this);
    other->accept(equal.get());
    return equal->isEqual;
}

bool SumOp::isLikeTerm(Symbol* other){return false;}

// void SumOp::appendChild(shared_ptr<Symbol>& child){
//     unique_ptr<AppendToSumOp> append = make_unique<AppendToSumOp>(*this, child);
//     child->accept(append.get());
// }

void SumOp::evaluateConstants(){
    int total = 0;
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
    if (change){
        if (total < 0){
            totalSign = false;
            total = total + (2 * (-1 * total));
        }
        shared_ptr<Symbol> summed = make_shared<Constant>(totalSign, total);
        if (children.size() == 0){
            // replace this with new constant
            parentExpression->replaceNode(this, summed);
        }else{
            appendChild(summed);
        }
    }
    // create new constant from total
    
}

void SumOp::evaluateSingleConstant(optional<int>& result, int& index, int& total, bool& totalSign){
    int val = *result;
    
    if (children[index]->getSign()){
        total += val;    
    }else{
        total -= val;
    }
    // removeChild(index);
    parentExpression->removeNode(children[index].get());
    index --;
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

void SumOp::sumLikeTerms(){
    for (int i = 0; i < children.size(); i ++){
        if (i + 1 != children.size()){
            for (int j = i + 1; j < children.size(); j ++){
                if (children[i]->isLikeTerm(children[j].get())){
                    // add the two together
                    // remove each
                    // append the added term
                }
            }
        }else{
            return;
        }
    }
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

shared_ptr<Symbol> SumOp::sanitise(){
    
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