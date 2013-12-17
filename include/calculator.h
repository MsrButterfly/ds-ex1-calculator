/**
 *  @file      calculator.h
 *  @brief     A calculator class for calculating a formula.
 *  @author    Darren Liu (MSR.B, msr-b)
 *  @date      2013/10/12
 *  @copyright Copyright (c) 2013 Darren Liu. All rights reserved.
 */

#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <iostream>
/// @brief   i did not use <string>, because i want to use pointers more
#include <cstring>
/// @brief   for using pow()
#include <cmath>
/// @brief   my string category, includes strtrm() for trimming strings and strrpl(n)() for replacing chars (4 overloads)
#include "string-category.h"
/// @brief   my range class for packaging few features
#include "range.h"
/// @brief   my data structure class of sequence list, i cannot use stl in this class after all...
#include "sequence-list.h"
/// @brief   my data structure class of stack, same as previous, it's also made by myself
#include "stack.h"

/// @brief   a calculator class provide string interpretation
class Calculator {
public:
    /**
     *  @brief constructor
     */
    Calculator() {}
    /**
     *  @brief  for calculate formula
     *
     *  @param  str            (const char *) formula string pointer
     *  @param  correctFormula (char*&) correct formula pointer
     *  @param  result         (double*) if interpretation succeded, return result of the formula
     *
     *  @return succeded or not
     *  @retval true           interpretation succeded
     *  @retval false          interpretation failed
     */
    bool calculate(const char *str, char *&correctFormula, double *result) {
        char *formula = new char[strlen(str) + 1];  // create a duplicate for str
        char *error = new char[100];
        strcpy(formula, str);
        removeIllogicalChars(formula);              // remove illogical chars, check syntax
        if (!checkSyntax(formula, error)) {
            std::cout << "Syntax error: " << error << std::endl;
            return false;                           // if syntax error occured, return false
        }
        correctFormula = new char[strlen(formula) + 1];
        strcpy(correctFormula, formula);            // create a duplicate for formula
        /** start calculate */
        {
            int i, l;
            int nint;              // int part
            double ndec;           // dec part
            double a;              // number 1
            double b;              // number 2
            int power;             // dec power
            char op1;              // left oprt
            char op2;              // right oprt
            char c;                // current char
            bool inInt;            // indicator of number parts
            strcat(formula, "#");  // add a '#' at the back of the formula
            l = strlen(formula);   // get the length of the formula
            Stack<char> oprt;      // operator stack
            Stack<double> nmbr;    // number stack
            oprt.push('#');        // push front '#'
            for (i = 0; i < l; i++) {
                if (numberList.in(c = formula[i])) {
                    // if this char is digital
                    inInt = true;             // start from int part
                    ndec = nint = power = 0;  // init all to 0
                    for (i = i; numberList.in(c); c = formula[++i]) {
                        // get the number
                        if (c == '.') {
                            // when meet '.' start adding dec part
                            inInt = false;
                            continue;
                        }
                        if (inInt) {
                            // if in int part
                            nint = nint * 10 + c - '0';
                        } else {
                            // or in dec part
                            power++;
                            ndec += (c - '0') / pow(10, power);
                            // i confess that it's not a good implementation
                        }
                    }
                    i--;  // because of the loop before, we must go back to last char
                    nmbr.push(nint + ndec);  // push our new number to the stack
                } else {
                    // or not
                    op1 = oprt.top();  // get the left operator
                    op2 = c;           // get the right operator
                    if (relation(op1, op2) < 0) {
                        // if the priority of left is lower than right
                        oprt.push(op2);            // push new operator to the stack
                    } else {
                        while (relation(op1, op2) > 0) {
                            // else while left is higher than right
                            oprt.pop();                      // pop left
                            b = nmbr.top();
                            nmbr.pop();                  // pop number 2
                            a = nmbr.top();
                            nmbr.pop();                  // pop number 1
                            if (op1 == '/' && b == 0) {
                                std::cout << "Can not divided by 0." << std::endl;
                                delete formula;          // don't forget to release!
                                delete error;
                                return false;
                            }
                            nmbr.push(execute(a, op1, b));   // caculate 1 left 2
                            op1 = oprt.top();                // assign new top to left
                        }
                        if (relation(op1, op2) == 0) {
                            // if left equals to right
                            oprt.pop();  // pop left (and right)
                            if (oprt.empty()) {
                                // if empty, that means '#' meats '#', stop calculating
                                break;
                            }
                        } else {
                            // else if left is lower than right
                            oprt.push(op2);  // push right in
                        }
                    }
                }
            }
            *result = nmbr.top();  // result is at the bottom of number stack
            nmbr.pop();
        }
        delete formula;    // don't forget to release!
        delete error;
        return true;       // calculate succeeded.
    }
private:
    /**
     *  @brief   remove illogical charactors in the formula
     *
     *  @param   (char*) formula
     */
    static void removeIllogicalChars(char *formula) {
        /** remove unknown chars in formula */
        {
            strrpln(formula, availableList, ' ');
            // replace all chars not in the available list
            strtrm(formula);
            // trim formula
        }
        /** remove illogical dots */
        {
            int i, l;
            bool dot;
            l = strlen(formula);  // get the length
            for (i = 0; i < l; i++) {
                dot = false;      // init dot flag before find next number
                for (; numberList.in(formula[i]) && i < l; i++) {
                    // if first char in number is found
                    if (formula[i] == '.') {
                        if (dot) {
                            // if there is already a dot
                            formula[i] = ' ';  // replace it with ' '
                            continue;          // goto next char
                        }
                        dot = true;  // else if first find, turn flag to true
                    }
                }
            }
            strtrm(formula);  // trim formula
        }
        /** replace brackets */
        {
            int i, l;
            l = strlen(formula);
            for (i = 0; i < l; i++) {
                if (leftBracketList.in(formula[i])) {
                    // if a left bracket is found
                    formula[i] = '(';  // replace it with '('
                } else if (rightBracketList.in(formula[i])) {
                    // if a right bracket is found
                    formula[i] = ')';  // replace it with ')'
                }
            }
        }
    }
    /**
     * @brief  check syntax of the formula
     *
     * @param  formula (const char*)  the formula
     * @param  error   (char*& error) error returning string
     *
     * @return bool
     * @retval true    error not found
     * @retval false   error found
     */
    static bool checkSyntax(const char *formula, char *&error) {
        int i, l, layer;
        bool num;
        l = strlen(formula);
        num = false;
        for (i = 0, layer = 0; i < l; i++) {
            if (formula[i] == '(') {
                // when meets '('
                layer++; // into a layer
                if (i > 0 && (numberList.in(formula[i - 1]) || formula[i - 1] == ')')) {
                    // the char at the left side of '(' can not be digital or '.' or ')'
                    error = (char *)("perators not found between brackets.");
                    return false;
                } else if (i < l - 1 && operatorList.in(formula[i + 1])) {
                    // the char at the right side of '(' can not be operator
                    error = (char *) "illogical operator found.";
                    return false;
                }
            } else if (formula[i] == ')') {
                // when meets ')'
                layer--; // escape a layer
                if (layer < 0) {
                    // '(' must at the front of ')'
                    error = (char *) "brackets did not match.";
                    return false;
                } else if (i + 1 < l && (numberList.in(formula[i + 1]) || formula[i + 1] == '(')) {
                    // the char at the right side of ')' can not be digital or '.' or '('
                    error = (char *) "operators not found between brackets.";
                    return false;
                } else if (i > 0 && operatorList.in(formula[i - 1])) {
                    // the char at the left side of ')' can not be operator
                    error = (char *) "illogical operator found.";
                    return false;
                }
            } else if (operatorList.in(formula[i])) {
                // can not have two consecutive operator
                // include *((()))*
                if (!num) {
                    error = (char *) "continuous operators found.";
                    return false;
                }
                num = false;
            } else {
                num = true;
            }
        }
        if (!num) {
            error = (char *) "no more number after the last operator.";
            return false;
        }
        if (layer) {
            // if brackets are not matching
            error = (char *) "brackets did not match.";
            return false;
        }
        return true;
    }
    /**
     * @brief  compare the priorities of two operators
     *
     * @param  left  (const char&) operator 1
     * @param  right (const char&) operator 2
     *
     * @return the difference between priorities of two operators
     * @retval relation>0 priority of operator 1 is higher than operator 2
     * @retval relation=0 priority of operator 1 is equal to operator 2
     * @retval relation<0 priority of operator 1 is lower than to operator 2
     */
    static int relation(const char &left, const char &right) {
        // return relation of operators (left - right)
        return lop[oprtNum(left)] - rop[oprtNum(right)];
    }
    /**
     * @brief  get operator sn
     *
     * @param  oprt       (const char&) operator
     *
     * @return operator sn
     * @retval 0        +
     * @retval 1        -
     * @retval 2        *
     * @retval 3        /
     * @retval 4        ^
     * @retval 5        (
     * @retval 6        )
     * @retval 7        #
     * @retval (exit)   others
     */
    static int oprtNum(const char &oprt) {
        // return sn of operator
        switch (oprt) {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '^':
            return 4;
        case '(':
            return 5;
        case ')':
            return 6;
        case '#':
            return 7;
        default:
            std::cerr << "Unknown operator" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    /**
     * @brief  calculate a simple formula
     *
     * @param  a    (const double&) number 1
     * @param  oprt (const char&) operator charactor
     * @param  b    (const double&) number 2
     * @return result
     */
    static double execute(const double &a, const char &oprt, const double b) {
        // calculate a simple formula
        switch (oprt) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            std::cerr << "Unknown operator" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    /// @name priority_variables
    /// @{
    /// @brief  priority of left operator
    static int lop[8];
    /// @brief  priority of right operator
    static int rop[8];
    /// @}
    /// @name lists
    /// @{
    /// @brief  operator list
    static SequenceList<char> operatorList    ;
    /// @brief  left bracket list
    static SequenceList<char> leftBracketList ;
    /// @brief  right bracket list
    static SequenceList<char> rightBracketList;
    /// @brief  number list
    static SequenceList<char> numberList      ;
    /// @brief  available list
    static SequenceList<char> availableList   ;
    /// @}
};

/// @name inits
/// @{
int                Calculator::lop[8]           = {3, 3, 5, 5, 7, 1, 8, 0};
int                Calculator::rop[8]           = {2, 2, 4, 4, 6, 8, 1, 0};

// init chars list
SequenceList<char> Calculator::operatorList     = {'+', '-', '*', '/', '^',
                                                   '\0'
                                                  };

SequenceList<char> Calculator::leftBracketList  = {'(', '[', '{', '<',
                                                   '\0'
                                                  };

SequenceList<char> Calculator::rightBracketList = {')', ']', '}', '>',
                                                   '\0'
                                                  };

// i have a smarter implementation of these two lists,
// but i can't place it on the outside of functions
// so i want to show it below
//
// SequenceList<char> Calculator::numberList = {'.', '\0'};
// Calculator::numberList.merge(Range<char>('0', '9'));
// SequenceList<char> Calculator::availableList = {'\0'};
// Calculator::numberList.merge(operatorList);
// Calculator::numberList.merge(leftBracketList);
// Calculator::numberList.merge(rightBracketList);
// Calculator::numberList.merge(numberList);

SequenceList<char> Calculator::numberList       = {'.', '0', '1', '2',
                                                   '3', '4', '5', '6',
                                                   '7', '8', '9', '\0'
                                                  };

SequenceList<char> Calculator::availableList    = {'+', '-', '*', '/', '^',
                                                   '(', '[', '{', '<',
                                                   ')', ']', '}', '>',
                                                   '.', '0', '1', '2',
                                                   '3', '4', '5', '6',
                                                   '7', '8', '9', '\0'
                                                  };
/// @}

#endif
