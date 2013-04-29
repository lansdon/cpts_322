//
//  Uppercase.cpp
//  tm
//
//	Utility functions for converting strings
// and chars to uppercase
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 4/5/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Uppercase.h"

#include <string>
#include <algorithm>


////////////////////////////
// Convert char to uppercase
////////////////////////////
char uppercase(char input) {
	return std::toupper(input);
}



////////////////////////////
// Convert string to uppercase
////////////////////////////
std::string uppercase(std::string input) {
	std::string result;
	std::transform(input.begin(), input.end(), std::back_inserter(result), ::toupper);
	return result;
}