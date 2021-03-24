// #pragma once

// #include "expression.h"
// #include "Fwd/fwdExpression.h"
// #include "Fwd/fwdSummation.h"
// #include "Fwd/fwdMultiplication.h"
// #include "Fwd/fwdDivision.h"
// #include "Fwd/fwdConstantExpression.h"
// #include "Fwd/fwdVariableExpression.h"

// class ExpressionFactory {

//     private:

//         ExpressionPtr expression;

//         bool tmpSign;

//         ExpressionPtr tmpRoot;

//         ExpressionPtr tmpExponent;

//         vector<ExpressionPtr> tmpOperands;

//         ExpressionPtr tmpNumerator;

//         ExpressionPtr tmpDenominator;

//         int tmpConstant;

//         char tmpVariable;

//     public:

//         ExpressionFactory();

//         ExpressionPtr get();

//         void reset();

//         // ExpressionFactory buildSummation(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, vector<ExpressionPtr>& operands);

//         // ExpressionFactory buildMultiplication(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, vector<ExpressionPtr>& operands);

//         // ExpressionFactory buildDivision(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, ExpressionPtr& numerator, ExpressionPtr& denominator);

//         // ExpressionFactory buildConstantExpression(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, int constant);

//         // ExpressionFactory buildVariableExpression(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, char variable);

//         // ExpressionFactory moveSummation();
    
//         // ExpressionFactory moveMultiplication();

//         // ExpressionFactory moveDivision();

//         // ExpressionFactory moveConstantExpression();

//         // ExpressionFactory moveVariableExpression();

//         ExpressionFactory buildSummation();

//         ExpressionFactory buildMultiplication();

//         ExpressionFactory buildDivision();

//         ExpressionFactory buildConstantExpression();        

//         ExpressionFactory buildVariableExpression();

//         ExpressionFactory sign(bool s);

//         ExpressionFactory root(Expression& r);

//         ExpressionFactory root(ExpressionPtr& r);

//         ExpressionFactory root(ExpressionPtr&& r);

//         ExpressionFactory exponent(Expression& e);

//         ExpressionFactory exponent(ExpressionPtr& e);

//         ExpressionFactory exponent(ExpressionPtr&& e);

//         ExpressionFactory operands(vector<ExpressionPtr>& o);

//         ExpressionFactory numerator(Expression& n);

//         ExpressionFactory numerator(ExpressionPtr& n);

//         ExpressionFactory numerator(ExpressionPtr&& n);

//         ExpressionFactory denominator(Expression& d);

//         ExpressionFactory denominator(ExpressionPtr& d);

//         ExpressionFactory denominator(ExpressionPtr&& d);

//         ExpressionFactory constant(int c);

//         ExpressionFactory variable(char v);




// };

// // =================== Implementation ===================




// // Expose methods from expression which need to be reached externally