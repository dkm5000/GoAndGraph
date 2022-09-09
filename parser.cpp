#include "parser.h"
#include <stack>
#include <iostream>
#include <math.h>

using namespace std;

Token::Token() { }

Token::Token(string t_str)
{
    string digits = "0123456789";
    if (digits.find(t_str[0]) < digits.size())
    {
        value = stod(t_str);
        type = "num";
    }
    else if (t_str == "(")
    {
        type = "lbr";
    }
    else if (t_str == ")")
    {
        type = "rbr";
    }
    else if (t_str == "+")
    {
        type = "oper";
        symbol = "+";
        associativity = "left";
        precedence = 10;
        parameters = 2;
    }
    else if (t_str == "-")
    {
        type = "oper";
        symbol = "-";
        associativity = "left";
        precedence = 10;
        parameters = 2;
    }
    else if (t_str == "*")
    {
        type = "oper";
        symbol = "*";
        associativity = "left";
        precedence = 20;
        parameters = 2;
    }
    else if (t_str == "/")
    {
        type = "oper";
        symbol = "/";
        associativity = "left";
        precedence = 20;
        parameters = 2;
    }
    else if (t_str == "^")
    {
        type = "oper";
        symbol = "^";
        associativity = "right";
        precedence = 40;
        parameters = 2;
    }
    else if (t_str == "x")
    {
        type = "var";
        symbol = "x";
    }
    else
    {
        cout << "Error: undefined type: " << t_str << endl;
    }
}

void Token::set_associativity(string assoc)
{
    associativity = assoc;
}

void Token::set_value(double val)
{
    value = val;
}

void Token::set_symbol(string symb)
{
    symbol = symb;
}

void Token::set_precedence(int pred)
{
    precedence = pred;
}

void Token::set_parameters(int param)
{
    parameters = param;
}

Expression::Expression() {};

Expression::Expression(string input_str)
{
    str = input_str;
}

void replace_all(string& str, string substr1, string substr2)
{
    int pos = 0;
    while (str.find(substr1, pos) < str.size())
    {
        pos = str.find(substr1, pos);
        str.replace(pos, substr1.size(), substr2);
        pos += substr2.size();
    }
}

void Expression::formating_str()
{
    replace_all(str, "(", " ( ");
    replace_all(str, ")", " ) ");
    replace_all(str, "+", " + ");
    replace_all(str, "-", " - ");
    replace_all(str, "*", " * ");
    replace_all(str, "/", " / ");
    replace_all(str, "^", " ^ ");

    str.append(" ");

    while (str.find("  ") < str.size())
    {
        replace_all(str, "  ", " ");
    }
    if (str[0] == ' ')
    {
        str.erase(0, 1);
    }
}

void Expression::get_tokens()
{
    formating_str();

    vector <string> str_tokens(0);
    int first = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == ' ')
        {
            str_tokens.push_back(str.substr(first, i - first));
            first = i + 1;
        }
    }

    for (int i = 0; i < str_tokens.size(); ++i)
    {
        Token t(str_tokens[i]);
        tokens.push_back(t);

        if (str_tokens[i] == "-" && (i == 0 || tokens[i - 1].get_type() == "oper" || tokens[i - 1].get_type() == "lbr"))
        {
            tokens[i].set_associativity("right");
            tokens[i].set_symbol("_");
            tokens[i].set_precedence(30);
            tokens[i].set_parameters(1);
        }
    }
}

void Expression::reverse_polish()
{
    stack<Token> operator_stack;

    get_tokens();

    for (int i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i].get_type() == "num" || tokens[i].get_type() == "var")
        {
            rpn_output.push_back(tokens[i]);
        }
        else if (tokens[i].get_type() == "oper")
        {
            while (!operator_stack.empty() &&
                    ((operator_stack.top().get_type() == "oper" || operator_stack.top().get_type() == "rbr") &&
                    (operator_stack.top().get_precedence() > tokens[i].get_precedence() ||
                    operator_stack.top().get_precedence() == tokens[i].get_precedence() &&
                    tokens[i].get_associativity() == "left")))
            {
                rpn_output.push_back(operator_stack.top());
                operator_stack.pop();
            }

            operator_stack.push(tokens[i]);
        }
        else if (tokens[i].get_type() == "lbr")
        {
            operator_stack.push(tokens[i]);
        }
        else if (tokens[i].get_type() == "rbr")
        {
            while (operator_stack.top().get_type() != "lbr")
            {
                try
                {
                    if (operator_stack.empty())
                    {
                        throw(1);
                    }
                }
                catch (int err)
                {
                    cout << "Mismatched parentheses\n" << " Error Nr. " << err;
                }

                rpn_output.push_back(operator_stack.top());
                operator_stack.pop();
            }

            try
            {
                if (operator_stack.top().get_type() != "lbr")
                {
                    throw(1);
                }
            }
            catch (int err)
            {
                cout << "Mismatched parentheses\n" << " Error Nr. " << err;
            }

            operator_stack.pop();
        }
    }

        while (!operator_stack.empty())
        {
            try
            {
                if (operator_stack.top().get_type() == "lbr" || operator_stack.top().get_type() == "rbr")
                {
                    throw(1);
                }
            }
            catch (int err)
            {
                cout << "Mismatched parentheses\n" << " Error Nr. " << err;
            }

            rpn_output.push_back(operator_stack.top());
            operator_stack.pop();
        }
}

void Expression::print_reverse_polish()
{
    for (int i = 0; i < rpn_output.size(); ++i)
    {
        if (rpn_output[i].get_type() == "num")
        {
            cout <<rpn_output[i].get_value();
        }
        else
        {
            cout << rpn_output[i].get_symbol();
        }
    }
}

Token operation(Token oper, vector<Token> operands)
{
    if (oper.get_symbol() == "+")
    {
        operands[0].set_value(operands[0].get_value() + operands[1].get_value());
    }
    else if (oper.get_symbol() == "-")
    {
        operands[0].set_value(operands[1].get_value() - operands[0].get_value());
    }
    else if (oper.get_symbol() == "_")
    {
        operands[0].set_value(-operands[0].get_value());
    }
    else if (oper.get_symbol() == "*")
    {
        operands[0].set_value(operands[0].get_value() * operands[1].get_value());
    }
    else if (oper.get_symbol() == "/")
    {
        operands[0].set_value(operands[1].get_value() / operands[0].get_value());
    }
    else if (oper.get_symbol() == "^")
    {
        operands[0].set_value(pow(operands[1].get_value(), operands[0].get_value()));
    }
    else
    {
        cout << "Error: unknown operator: " << oper.get_symbol() << endl;
    }

    return operands[0];
}

double Expression::calculate(double x)
{
    reverse_polish();
    
    stack<Token> value_stack;

    for (int i = 0; i < rpn_output.size(); ++i)
    {
        if (rpn_output[i].get_type() == "num")
        {
            value_stack.push(rpn_output[i]);
        }
        else if (rpn_output[i].get_type() == "var")
        {
            rpn_output[i].set_value(x);
            value_stack.push(rpn_output[i]);
        }
        else if (rpn_output[i].get_type() == "oper")
        {
            try
            {
                if (value_stack.size() < rpn_output[i].get_parameters())
                {
                    throw(2);
                }
            }
            catch(int err)
            {
                cout << "Error " << err << ": insufficient values in the expression";
            }

            vector<Token> operands(0);

            for (int j = 0; j < rpn_output[i].get_parameters(); ++j)
            {
                operands.push_back(value_stack.top());
                value_stack.pop();
            }

            operands[0] = operation(rpn_output[i], operands);
            value_stack.push(operands[0]);
        }
    }

    try
    {
        if (value_stack.size() != 1)
        {
            throw(3);
        }
    }
    catch(int err)
    {
        cout << "Error " << err << ": too many values";
    }
    return value_stack.top().get_value();
}



