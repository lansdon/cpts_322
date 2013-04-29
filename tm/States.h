//
//  States.h
//  tm
// Represents the list of valid states
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__States__
#define __tm__States__

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "String_Pointer.h"
#include "Uppercase.h"

using namespace std;


class States
{
public:
	/////////////////////////////////////
	// Loads the states from the given definition file and sets valid to true if it was successful, else false.
	/////////////////////////////////////
	void load(ifstream& definition, bool& valid);
	
	/////////////////////////////////////
	// displays the current set of states
	/////////////////////////////////////
	void view() const;
	
	/////////////////////////////////////
	// Returns true if value is found in the set of states.
	/////////////////////////////////////
	bool is_element(string value) const ;
	
//	static int total_number_of_states() { return number_of_states; }
	
		
private:
	vector<string> states;
//	static int number_of_states;
	
};


#endif /* defined(__tm__States__) */
