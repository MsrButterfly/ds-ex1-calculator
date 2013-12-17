/**
 *  @file      stack.h
 *  @brief     Data structure: stack
 *  @author    Darren Liu (MSR.B, msr-b)
 *  @date      2013/10/13
 *  @copyright Copyright (c) 2013 Darren Liu. All rights reserved.
 */

#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <cstdlib>

/**
 *  @brief Data structure: stack
 */
template <typename _Ty>
class Stack {
public:
    /**
     *  @brief  constructor of stack
     */
    Stack() : _top(NULL) {}
    /**
     *  @brief  push element into the stack
     *
     *  @param  data  (const _Ty&) the element
     *
     *  @return succeeded or not
     *  @retval true  push succeded
     *  @retval false push failed
     */
    bool push(const _Ty &data) {
        StackNode *top = new StackNode(data, _top);
        if (!top) {
            return false;
        }
        _top = top;
        return true;
    }
    /**
     *  @brief  remove the top element
     *
     *  @return succeed or not
     *  @retval true  pop succeded
     *  @retval false pop failed
     *  @see _Ty top() const
     */
    bool pop() {
        if (empty()) {
            return false;
        }
        StackNode *top = _top;
        _top = _top -> next;
        delete top;
        return true;
    }
    /**
     *  @brief  test whether the stack is empty
     *
     *  @return empty or not
     *  @retval true   empty
     *  @retval false  not empty
     */
    bool empty() {
        return (_top) ? false : true;
    }
    /**
     *  @brief  return the top element
     *
     *  @return top element
     */
    _Ty top() const {
        if (!_top) {
            std::cerr << "No elements in stack." << std::endl;
            exit(EXIT_FAILURE);
        }
        return _top -> data;
    }
    /// @brief  destructor of stack
    ~Stack() {
        StackNode *top = _top;
        for (; top; top = _top) {
            _top = _top -> next;
            delete top;
        }
    }
private:
    class StackNode {
    public:
        StackNode(const _Ty &data, StackNode *next = NULL) : data(data), next(next) {}
        _Ty data;
        StackNode *next;
    };
    /// @brief top pointer
    StackNode *_top;
};

#endif
