/**
 *  @file      calculator.cpp
 *  @brief     A calculator in console.
 *  @details   Program for data structure experiment.
 *             Tested under g++ (4.8.1) and clang (sorry for forgetting the version...).
 *             Usage: g++ -std=c++11 calculator.cpp -o calculator.exe
 *             *-std=c++11 is an importent switch.
 *             *It will generate some warnings, please ignore it.
 *             I haven't use any IDE, so there is no other files, please compile by yourself.
 *  @author    Darren Liu (MSR.B, msr-b)
 *  @date      2013/10/10
 *  @copyright Copyright (c) 2013 Darren Liu. All rights reserved.
 */

/// @brief Debug switch, will enable file input
// #define __DEBUG__

#include <iostream>
#ifdef __DEBUG__
	#include <fstream>
#endif
#include "include/calculator.h"

/**
 *  @brief entry of the console application
 *  @param argc  number of console parameters
 *  @param argv  console parameter strings
 */
int main(int argc, char const *argv[]) {
	char formula[1000];    // formula string
	char* correctFormula;  // pointer for receiving correct formula
	double result;         // variable for receiving result
	Calculator c;          // calculator for calculating
	#ifdef __DEBUG__       // debug switch, redirect input to file(calculater.in)
		std::ifstream fin("calculator.in");
		std::cin.rdbuf(fin.rdbuf());
	#endif
	while (std::cin.getline(formula, 999)) {
		// std::cout << "formula: " << formula << std::endl;  // print original formula
		if (c.calculate(formula, correctFormula, &result)) {
		// if calculate succeeded
			std::cout << correctFormula << " = " << result << std::endl;
		}
		// an extra line for segmentation
	}
	return 0;
}
