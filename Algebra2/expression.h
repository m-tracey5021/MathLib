#pragma once

class ExpressionContainer;
class Expression;
class Summation;
class Multiplication;
class Division;
class ConstantExpression;
class VariableExpression;

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;

// #define up unique_ptr
// #define mup make_unique

class ExpressionContainer {

    private:

        Expression* expression;

        // Private copy

        

    public:

        ExpressionContainer(); // Default constructor

        ExpressionContainer(Expression& e);

        ExpressionContainer(const ExpressionContainer& ec); // Copy constructor

        ExpressionContainer(ExpressionContainer&& ec); // Move constructor

        ExpressionContainer& operator=(const ExpressionContainer& ec); // Assignment overload

        //~ExpressionContainer(); // Destructor

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

        // Test

        bool isEmpty();

        // Public copy

        // Expression subclasses actually do the 'newing' of pointers, but only return containers, so that no pointers are left dangling. The copy function from
        // within ExpressionContainer takes the pointer returned from the container and assigns it to the wrapped pointer

        ExpressionContainer copyContainer(bool deep = true);

        Expression* deepCopy();

        Expression* shallowCopy();

        // Exposed methods

        vector<ExpressionContainer> getContent();

};

class Expression {

    protected:

        bool sign;

        ExpressionContainer root;

        ExpressionContainer exponent;

        ExpressionContainer parentExpression;

        string expressionString;

    public:

        Expression();

        Expression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent);

        Expression(bool sign, ExpressionContainer&& root, ExpressionContainer&& exponent);

        virtual ExpressionContainer copyExpression() = 0; // copyToContainer ?

        virtual vector<ExpressionContainer> getContent() = 0;

};

class Summation : public Expression {

    private:

        vector<ExpressionContainer> operands;

    public:

        Summation(); // Default

        Summation(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, vector<ExpressionContainer>& operands); // Custom

        //Summation(const Summation& s); // Copy

        ExpressionContainer copyExpression() override;

        vector<ExpressionContainer> getContent() override;

};

class Multiplication : public Expression {

    private:

        vector<ExpressionContainer> operands;

    public:

        Multiplication(); // Default

        Multiplication(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, vector<ExpressionContainer>& operands); // Custom

        //Multiplication(const Multiplication& m); // Copy

        ExpressionContainer copyExpression() override;

        vector<ExpressionContainer> getContent() override;
    
};

class Division : public Expression {

    private:

        ExpressionContainer numerator;

        ExpressionContainer denominator;

    public:

        Division();

        Division(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, ExpressionContainer& numerator, ExpressionContainer& denominator);

        //Division(const Division& d);

        ExpressionContainer copyExpression() override;

        vector<ExpressionContainer> getContent() override;

};

class ConstantExpression : public Expression {

    private:

        int constant;

    public:

        ConstantExpression();

        ConstantExpression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, int constant);

        //ConstantExpression(const ConstantExpression& c);

        ExpressionContainer copyExpression() override;

        vector<ExpressionContainer> getContent() override;

};

class VariableExpression : public Expression {

    private:

        char variable;

    public:

        VariableExpression();

        VariableExpression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, char variable);

        //VariableExpression(const VariableExpression& v);

        ExpressionContainer copyExpression() override;

        vector<ExpressionContainer> getContent() override;

};

