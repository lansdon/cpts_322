//
//  Uppercase.cpp
//  tm
//
//  Created by Lansdon Page on 4/5/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Uppercase.h"

#include <string>
#include <algorithm>


std::string uppercase(std::string input) {
	std::string result;
	std::transform(input.begin(), input.end(), std::back_inserter(result), ::toupper);
	return result;
}