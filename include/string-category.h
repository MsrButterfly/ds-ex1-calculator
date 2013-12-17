/**
 *  @file      string-category.h
 *  @brief     My cstring category for c++.
 *  @author    Darren Liu (MSR.B, msr-b)
 *  @date      2013/10/12
 *  @copyright Copyright (c) 2013 Darren Liu. All rights reserved.
 */

#ifndef _STRING_CATEGORY_H_
#define _STRING_CATEGORY_H_
#include <cstring>
#include "range.h"
#include "sequence-list.h"

/**
 *  @brief  replace charactors in specific range
 *
 *  @param  str   (char*) string
 *  @param  range (Range<char>) charactor range
 *  @param  to    (char) replace to
 *
 *  @return amount of charactors replaced
 */
int strrpl(char *str, Range<char> range, char to) {
    int i, n = 0, l = strlen(str);
    for (i = 0; i < l; i++) {
        if (range.in(str[i])) {
            str[i] = to;
            n++;
        }
    }
    return n;
}

/**
 *  @brief  replace charactors in specific list
 *
 *  @param  str  (char*) string
 *  @param  list (SequenceList<char>) charactor list
 *  @param  to   (char) replace to
 *
 *  @return amount of charactors replaced
 */
int strrpl(char *str, SequenceList<char> list, char to) {
    int i, n = 0, l = strlen(str);
    for (i = 0; i < l; i++) {
        if (list.in(str[i])) {
            str[i] = to;
        }
    }
    return n;
}

/**
 *  @brief  replace charactors *not* in specific range
 *
 *  @param  str   (char*) string
 *  @param  range (Range<char>) charactor range
 *  @param  to    (char) replace to
 *
 *  @return amount of charactors replaced
 */
int strrpln(char *str, Range<char> range, char to) {
    int i, n = 0, l = strlen(str);
    for (i = 0; i < l; i++) {
        if (!range.in(str[i])) {
            str[i] = to;
            n++;
        }
    }
    return n;
}

/**
 *  @brief  replace charactors *not* in specific list
 *
 *  @param  str  (char*) string
 *  @param  list (SequenceList<char>) charactor list
 *  @param  to   (char) replace to
 *
 *  @return amount of charactors replaced
 */
int strrpln(char *str, SequenceList<char> list, char to) {
    int i, n = 0, l = strlen(str);
    for (i = 0; i < l; i++) {
        if (!list.in(str[i])) {
            str[i] = to;
        }
    }
    return n;
}

/**
 *  @brief  remove spaces and tabs in string
 *
 *  @param  str  (char*) string
 *
 *  @return amount of charactors deleted
 */
int strtrm(char *str) {
    char *p;
    int n = 0;
    for (p = str; *str != '\0'; str++) {
        if (*str != ' ' && *str != '\t') {
            * (p++) = *str;
        } else {
            n++;
        }
    }
    *p = '\0';
    return n;
}
#endif
