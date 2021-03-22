#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Fwd/fwdExpressionFactory.h"
#include "Fwd/fwdExpression.h"
#include "Fwd/fwdSummation.h"
#include "Fwd/fwdMultiplication.h"
#include "Fwd/fwdDivision.h"
#include "Fwd/fwdConstantExpression.h"
#include "Fwd/fwdVariableExpression.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;

// class ExpressionFactory;
// class Expression;
// class Summation;
// class Multiplication;
// class Division;
// class ConstantExpression;
// class VariableExpression;

typedef unique_ptr<Expression> ExpressionPtr;
typedef unique_ptr<ConstantExpression> CEPtr;
typedef unique_ptr<VariableExpression> VEPtr;
typedef unique_ptr<int> IntPtr;

class Expression {

    protected:

        bool sign;

        ExpressionPtr root;

        ExpressionPtr exponent;

        ExpressionPtr parentExpression;

        string expressionString;

    public:

        Expression();

        Expression(bool sign, ExpressionPtr& root, ExpressionPtr& exponent);

        //virtual ~Expression();

        bool getSign();

        ExpressionPtr getRoot();

        ExpressionPtr getExponent();

        ExpressionPtr getParentExpression();

        string getExpressionString();

        void setSign(bool s);

        void setRoot(ExpressionPtr& e);

        void setExponent(ExpressionPtr& e);

        void setParentExpression(ExpressionPtr& e);

        void updateExpressionString();

        void getAllSubTerms(vector<ExpressionPtr>& terms,
                                vector<ExpressionPtr>& subTerms,
                                int start,
                                int end);

        //  === Virtual methods ===

        // Get

        virtual IntPtr getValue() = 0;

        virtual vector<ExpressionPtr> getContent() = 0;

        // Append/Remove/Replace

        virtual void appendExpression(Expression& e) = 0;

        virtual void removeExpression(int i) = 0;

        virtual void replaceExpression(int i, Expression& e) = 0;

        // Clean

        virtual void sanitise() = 0;

        // Test

        virtual bool isEqual(Expression& other) = 0;

        virtual bool isEqual(Summation& other) = 0;

        virtual bool isEqual(Multiplication& other) = 0;

        virtual bool isEqual(Division& other) = 0;

        virtual bool isEqual(ConstantExpression& other) = 0;

        virtual bool isEqual(VariableExpression& other) = 0;

        virtual bool isOne() = 0;

        virtual bool isAtomic() = 0;

        virtual bool isAtomicExponent() = 0;

        virtual bool isAtomicNumerator() = 0;

        virtual bool isLikeExpression(Expression& e) = 0;

        virtual bool isMergeable() = 0;

        // Manipulate

        virtual ExpressionPtr sum(Summation& s) = 0;
        virtual ExpressionPtr sum(Multiplication& m) = 0;
        virtual ExpressionPtr sum(Division& d) = 0;
        virtual ExpressionPtr sum(ConstantExpression& c) = 0;
        virtual ExpressionPtr sum(VariableExpression& v) = 0;

        virtual ExpressionPtr multiply(Summation& s) = 0;
        virtual ExpressionPtr multiply(Multiplication& m) = 0;
        virtual ExpressionPtr multiply(Division& d) = 0;
        virtual ExpressionPtr multiply(ConstantExpression& c) = 0;
        virtual ExpressionPtr multiply(VariableExpression& v) = 0;

        virtual ExpressionPtr divide(Summation& s) = 0;
        virtual ExpressionPtr divide(Multiplication& m) = 0;
        virtual ExpressionPtr divide(Division& d) = 0;
        virtual ExpressionPtr divide(ConstantExpression& c) = 0;
        virtual ExpressionPtr divide(VariableExpression& v) = 0;

        virtual ExpressionPtr mergeMultiplications(Expression& e) = 0;

        virtual ExpressionPtr expandForExponent() = 0;

        virtual ExpressionPtr expandAsExponent(Expression& baseExpression) = 0;

        virtual ExpressionPtr expandAsConstNum(Expression& baseExpression, Expression& baseDivision) = 0;

        virtual ExpressionPtr expandAsNegativeExponent(Expression& baseExpression) = 0;

        virtual ExpressionPtr factor() = 0;

        virtual vector<ExpressionPtr> getConstantFactors() = 0;

        virtual vector<ExpressionPtr> getAllFactors() = 0;

        // Misc

        virtual ExpressionPtr copy() = 0;

        //virtual ExpressionPtr reassign() = 0;

        //virtual ExpressionPtr shallowCopy() = 0;

        //virtual ExpressionPtr deepCopy() = 0;

        virtual string toString() = 0;

        virtual string exponentToString() = 0;




};

class Summation : public Expression {

    private:

        vector<ExpressionPtr> operands;

    public:

        Summation();

        Summation(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, vector<ExpressionPtr>& operands);

        // ~Summation();

        vector<ExpressionPtr> getOperands();

        void setOperands(vector<ExpressionPtr>& o);

        // Overrides

        // Get

        IntPtr getValue() override;

        vector<ExpressionPtr> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionPtr sum(Summation& s) override;
        ExpressionPtr sum(Multiplication& m) override;
        ExpressionPtr sum(Division& d) override;
        ExpressionPtr sum(ConstantExpression& c) override;
        ExpressionPtr sum(VariableExpression& v) override;

        ExpressionPtr multiply(Summation& s) override;
        ExpressionPtr multiply(Multiplication& m) override;
        ExpressionPtr multiply(Division& d) override;
        ExpressionPtr multiply(ConstantExpression& c) override;
        ExpressionPtr multiply(VariableExpression& v) override;

        ExpressionPtr divide(Summation& s) override;
        ExpressionPtr divide(Multiplication& m) override;
        ExpressionPtr divide(Division& d) override;
        ExpressionPtr divide(ConstantExpression& c) override;
        ExpressionPtr divide(VariableExpression& v) override;

        ExpressionPtr mergeMultiplications(Expression& e) override;

        ExpressionPtr expandForExponent() override;

        ExpressionPtr expandAsExponent(Expression& baseExpression) override;

        ExpressionPtr expandAsConstNum(Expression& baseExpression, Expression& baseDivision) override;

        ExpressionPtr expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionPtr factor() override;

        vector<ExpressionPtr> getConstantFactors() override;

        vector<ExpressionPtr> getAllFactors() override;

        // Misc

        ExpressionPtr copy() override;

        //ExpressionPtr shallowCopy() override;

        string toString() override;

        string exponentToString() override;

};

class Multiplication : public Expression {

    private:

        vector<ExpressionPtr> operands;

    public:

        Multiplication();

        Multiplication(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, vector<ExpressionPtr>& operands);

        //~Multiplication() override;

        vector<ExpressionPtr> getOperands();

        void setOperands(vector<ExpressionPtr>& operands);

        // Overrides

        // Get

        IntPtr getValue() override;

        vector<ExpressionPtr> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionPtr sum(Summation& s) override;
        ExpressionPtr sum(Multiplication& m) override;
        ExpressionPtr sum(Division& d) override;
        ExpressionPtr sum(ConstantExpression& c) override;
        ExpressionPtr sum(VariableExpression& v) override;

        ExpressionPtr multiply(Summation& s) override;
        ExpressionPtr multiply(Multiplication& m) override;
        ExpressionPtr multiply(Division& d) override;
        ExpressionPtr multiply(ConstantExpression& c) override;
        ExpressionPtr multiply(VariableExpression& v) override;

        ExpressionPtr divide(Summation& s) override;
        ExpressionPtr divide(Multiplication& m) override;
        ExpressionPtr divide(Division& d) override;
        ExpressionPtr divide(ConstantExpression& c) override;
        ExpressionPtr divide(VariableExpression& v) override;

        ExpressionPtr mergeMultiplications(Expression& e) override;

        ExpressionPtr expandForExponent() override;

        ExpressionPtr expandAsExponent(Expression& baseExpression) override;

        ExpressionPtr expandAsConstNum(Expression& baseExpression, Expression& baseDivision) override;

        ExpressionPtr expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionPtr factor() override;

        vector<ExpressionPtr> getConstantFactors() override;

        vector<ExpressionPtr> getAllFactors() override;

        // Misc

        ExpressionPtr copy() override;

        string toString() override;

        string exponentToString() override;
    
};

class Division : public Expression {

    private:

        ExpressionPtr numerator;

        ExpressionPtr denominator;

    public:

        Division();

        Division(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, ExpressionPtr& numerator, ExpressionPtr& denominator);

        // ~Division();

        ExpressionPtr getNumerator();

        ExpressionPtr getDenominator();

        void setNumerator(ExpressionPtr& n);

        void setDenominator(ExpressionPtr& d);

        // Overrides

        // Get

        IntPtr getValue() override;

        vector<ExpressionPtr> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionPtr sum(Summation& s) override;
        ExpressionPtr sum(Multiplication& m) override;
        ExpressionPtr sum(Division& d) override;
        ExpressionPtr sum(ConstantExpression& c) override;
        ExpressionPtr sum(VariableExpression& v) override;

        ExpressionPtr multiply(Summation& s) override;
        ExpressionPtr multiply(Multiplication& m) override;
        ExpressionPtr multiply(Division& d) override;
        ExpressionPtr multiply(ConstantExpression& c) override;
        ExpressionPtr multiply(VariableExpression& v) override;

        ExpressionPtr divide(Summation& s) override;
        ExpressionPtr divide(Multiplication& m) override;
        ExpressionPtr divide(Division& d) override;
        ExpressionPtr divide(ConstantExpression& c) override;
        ExpressionPtr divide(VariableExpression& v) override;

        ExpressionPtr mergeMultiplications(Expression& e) override;

        ExpressionPtr expandForExponent() override;

        ExpressionPtr expandAsExponent(Expression& baseExpression) override;

        ExpressionPtr expandAsConstNum(Expression& baseExpression, Expression& baseDivision) override;

        ExpressionPtr expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionPtr factor() override;

        vector<ExpressionPtr> getConstantFactors() override;

        vector<ExpressionPtr> getAllFactors() override;

        // Misc

        ExpressionPtr copy() override;

        string toString() override;

        string exponentToString() override;

};

class ConstantExpression : public Expression {

    private:

        int constant;

    public:

        ConstantExpression();

        ConstantExpression(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, int constant);

        // ~ConstantExpression();

        int getConstant();

        void setConstant(int c);

        // Overrides

        // Get

        IntPtr getValue() override;

        vector<ExpressionPtr> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionPtr sum(Summation& s) override;
        ExpressionPtr sum(Multiplication& m) override;
        ExpressionPtr sum(Division& d) override;
        ExpressionPtr sum(ConstantExpression& c) override;
        ExpressionPtr sum(VariableExpression& v) override;

        ExpressionPtr multiply(Summation& s) override;
        ExpressionPtr multiply(Multiplication& m) override;
        ExpressionPtr multiply(Division& d) override;
        ExpressionPtr multiply(ConstantExpression& c) override;
        ExpressionPtr multiply(VariableExpression& v) override;

        ExpressionPtr divide(Summation& s) override;
        ExpressionPtr divide(Multiplication& m) override;
        ExpressionPtr divide(Division& d) override;
        ExpressionPtr divide(ConstantExpression& c) override;
        ExpressionPtr divide(VariableExpression& v) override;

        ExpressionPtr mergeMultiplications(Expression& e) override;

        ExpressionPtr expandForExponent() override;

        ExpressionPtr expandAsExponent(Expression& baseExpression) override;

        ExpressionPtr expandAsConstNum(Expression& baseExpression, Expression& baseDivision) override;

        ExpressionPtr expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionPtr factor() override;

        vector<ExpressionPtr> getConstantFactors() override;

        vector<ExpressionPtr> getAllFactors() override;

        // Misc

        ExpressionPtr copy() override;

        string toString() override;

        string exponentToString() override;

};

class VariableExpression : public Expression {

    private:

        char variable;

    public:

        VariableExpression();

        VariableExpression(bool sign, ExpressionPtr& root, ExpressionPtr& exponent, char variable);

        // ~VariableExpression();

        char getVariable();

        void setVariable(char v);

        // Overrides

        // Get

        IntPtr getValue() override;

        vector<ExpressionPtr> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionPtr sum(Summation& s) override;
        ExpressionPtr sum(Multiplication& m) override;
        ExpressionPtr sum(Division& d) override;
        ExpressionPtr sum(ConstantExpression& c) override;
        ExpressionPtr sum(VariableExpression& v) override;

        ExpressionPtr multiply(Summation& s) override;
        ExpressionPtr multiply(Multiplication& m) override;
        ExpressionPtr multiply(Division& d) override;
        ExpressionPtr multiply(ConstantExpression& c) override;
        ExpressionPtr multiply(VariableExpression& v) override;

        ExpressionPtr divide(Summation& s) override;
        ExpressionPtr divide(Multiplication& m) override;
        ExpressionPtr divide(Division& d) override;
        ExpressionPtr divide(ConstantExpression& c) override;
        ExpressionPtr divide(VariableExpression& v) override;

        ExpressionPtr mergeMultiplications(Expression& e) override;

        ExpressionPtr expandForExponent() override;

        ExpressionPtr expandAsExponent(Expression& baseExpression) override;

        ExpressionPtr expandAsConstNum(Expression& baseExpression, Expression& baseDivision) override;

        ExpressionPtr expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionPtr factor() override;

        vector<ExpressionPtr> getConstantFactors() override;

        vector<ExpressionPtr> getAllFactors() override;

        // Misc

        ExpressionPtr copy() override;

        string toString() override;

        string exponentToString() override;
};

