#pragma once

#include "expressionDeclarations.h"
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;

class ExpressionContainer {

    private:

        unique_ptr<Expression> expression;

        unique_ptr<Expression> getExpression();

    public:

        ExpressionContainer();

        ExpressionContainer(const ExpressionContainer& ec);

        ExpressionContainer& operator= (const ExpressionContainer& ec);

        // Build expression overloads

        void buildSummation();

        void buildSummation(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, vector<ExpressionContainer>& operands);

        void buildMultiplication();

        void buildMultiplication(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, vector<ExpressionContainer>& operands);

        void buildDivision();

        void buildDivision(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, ExpressionContainer& numerator, ExpressionContainer& denominator);

        void buildConstantExpression();

        void buildConstantExpression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, int constant);

        void buildVariableExpression();

        void buildVariableExpression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, char variable);

        // Assignment overloads

        void assignExpression(unique_ptr<Expression>& up);

        void assignExpression(ExpressionContainer& ec);

};

// =================== Implementation ===================

ExpressionContainer::ExpressionContainer(){}

ExpressionContainer::ExpressionContainer(const ExpressionContainer& ec): expression(move(expression)){}

ExpressionContainer& ExpressionContainer::operator= (const ExpressionContainer& ec){
    expression = move(ec.expression);
}

unique_ptr<Expression> ExpressionContainer::getExpression(){
    return move(expression);
}

void ExpressionContainer::buildSummation(){
    ExpressionContainer emptyRoot();
    ExpressionContainer emptyExponent();
    vector<ExpressionContainer> emptyOperands;
    expression = make_unique<Summation>(true, emptyRoot, emptyExponent, emptyOperands);
}

void ExpressionContainer::buildMultiplication(){
    ExpressionContainer emptyRoot();
    ExpressionContainer emptyExponent();
    vector<ExpressionContainer> emptyOperands;
    expression = make_unique<Multiplication>(true, emptyRoot, emptyExponent, emptyOperands);
}

void ExpressionContainer::buildDivision(){
    ExpressionContainer emptyRoot();
    ExpressionContainer emptyExponent();
    ExpressionContainer emptyNumerator();
    ExpressionContainer emptyDenominator();
    expression = make_unique<Division>(true, emptyRoot, emptyExponent, emptyNumerator, emptyDenominator);
}

void ExpressionContainer::buildConstantExpression(){
    ExpressionContainer emptyRoot();
    ExpressionContainer emptyExponent();
    expression = make_unique<Summation>(true, emptyRoot, emptyExponent, 1);
}

void ExpressionContainer::buildVariableExpression(){
    ExpressionContainer emptyRoot();
    ExpressionContainer emptyExponent();
    vector<ExpressionContainer> emptyOperands;
    expression = make_unique<Summation>(true, emptyRoot, emptyExponent, '_');
}

// Expose methods from expression which need to be reached externally