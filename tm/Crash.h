//
//  Crash.h
//  tm
//
//  Created by Lansdon Page on 4/1/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__Crash__
#define __tm__Crash__

#include <exception>
#include <string>
using namespace std;

class Crash : public exception
{
public:
		explicit Crash (const std::string& what_arg) : description(what_arg) {}
		explicit Crash (const char* what_arg) : description(std::string(what_arg)) {}

		virtual const char* what() const noexcept {
			return description.c_str();
		}
	private:
		std::string description;
};

#endif /* defined(__tm__Crash__) */
