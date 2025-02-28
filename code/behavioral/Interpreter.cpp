/*
The Interpreter pattern is a behavioral design pattern used to define a grammar for
a language and provide an interpreter to evaluate sentences in that language.

Problem Solved by the Interpreter Pattern

Imagine you need to evaluate simple mathematical expressions like:
3 + 5
2 * (3 + 4)
Without the Interpreter pattern, manually parsing and evaluating such expressions can be complex.
💡 Solution:
The Interpreter pattern provides a structured way to represent and evaluate expressions by:
✅ Defining rules (Grammar)
✅ Creating a syntax tree
✅ Evaluating expressions recursively

📌 Where is it Used?
✅ Mathematical Expression Evaluators (e.g., simple calculators)
✅ SQL Query Parsers (Translating text queries into database operations)
✅ Programming Language Compilers (Parsing and interpreting language syntax)
✅ Regular Expression Matching (Evaluating regex rules)

🚫 Drawbacks of the Interpreter Pattern
❌ Complexity grows fast as grammar becomes more advanced
❌ Performance issues in large-scale parsing (use a parser generator instead)
❌ Not suitable for complex languages (better handled with tools like ANTLR, yacc, or Boost Spirit)
*/

#include <iostream>
#include <memory>

class Expression
{
public:
    virtual int interpret() = 0;
    virtual ~Expression() = default;
};

class NumberExpression : public Expression
{
private:
    int number;

public:
    NumberExpression(int number)
        : number(number) {}
    int interpret() override { return number; }
};

class AdditionExpression : public Expression
{
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

public:
    AdditionExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}
    int interpret() override
    {
        return left->interpret() + right->interpret();
    }
};

class MultiplicationExpression : public Expression
{
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

public:
    MultiplicationExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}
    int interpret() override
    {
        return left->interpret() * right->interpret();
    }
};

class SubtractionExpression : public Expression
{
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

public:
    SubtractionExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}
    int interpret() override
    {
        return left->interpret() - right->interpret();
    }
};

int main(int argc, const char **argv)
{
    auto five = std::make_shared<NumberExpression>(5);
    auto three = std::make_shared<NumberExpression>(3);
    auto four = std::make_shared<NumberExpression>(4);

    auto addition = std::make_shared<AdditionExpression>(five, three);
    std::cout << addition->interpret() << std::endl;

    auto multiplication = std::make_shared<MultiplicationExpression>(five, four);
    std::cout << multiplication->interpret() << std::endl;

    // (5+3) * 4
    auto expression = std::make_shared<MultiplicationExpression>(addition, four);
    std::cout << expression->interpret() << std::endl;

    return 0;
}
