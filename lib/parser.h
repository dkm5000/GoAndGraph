#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <string>
#include <queue>

using namespace std;

class Token
{
public:
    Token();

    Token(string str);


    string get_type() { return type; };
    string get_symbol() { return symbol; };
    int get_precedence() { return precedence; };
    int get_parameters() { return parameters; };
    double get_value() { return value; };
    string get_associativity() { return associativity; };
    bool get_incl_var() { return incl_var; };

    void set_associativity(string assoc);
    void set_incl_var(bool v);
    void set_symbol(string symb);
    void set_precedence(int pred);
    void set_parameters(int param);
    void set_value(double val);

private:
    string type;                    // num, oper, func, var, lbr, rbr
    string associativity;           // left, right
    string symbol;
    bool incl_var = 0;
    double value;
    int precedence;
    int parameters;
};

class Expression
{
public:
    Expression();
    Expression(string input_str);

    void formating_str();

    void get_tokens();
    string get_str() { return str; };

    void reverse_polish();

    double calculate(double x);

    void print_reverse_polish();

private:
    double from;
    double to;
    string str;
    vector <Token> tokens;
    vector<Token> rpn_output;
};

#endif // PARSER_H_INCLUDED
