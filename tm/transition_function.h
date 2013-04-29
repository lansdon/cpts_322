//
//  transition_function.h
//  tm
//
//	Represents the list of defined transitions
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__transition_function__
#define __tm__transition_function__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Transition.h"
#include "Direction.h"
#include "Uppercase.h"
using namespace std;


class Transition_Function
{
public:
	////////////////////////////////////////////
	// Loads the transitions from the definition_file. Sets valid to true on success, else false.
	////////////////////////////////////////////
	void load(ifstream& definition, bool& valid);

	////////////////////////////////////////////
	//	Displays the loaded transitions
	////////////////////////////////////////////
	void view() const;

	////////////////////////////////////////////
	// Returns the number of stored transitions
	////////////////////////////////////////////
	int size() const;
	
	////////////////////////////////////////////
	// return source state
	////////////////////////////////////////////
	string source_state(unsigned long index) const;

	////////////////////////////////////////////
	// return read char
	////////////////////////////////////////////
	char read_character(unsigned long index) const;

	////////////////////////////////////////////
	// return detination state
	////////////////////////////////////////////
	string destination_state(unsigned long index) const;

	////////////////////////////////////////////
	// write char of given transition
	////////////////////////////////////////////
	char write_character(unsigned long index) const;

	////////////////////////////////////////////
	// move direction of given transition
	////////////////////////////////////////////
	Direction move_direction(unsigned long index) const;

	
	////////////////////////////////////////////
	// Find a matching saved transition
	////////////////////////////////////////////
	bool is_defined_transition(string source_state,
							   char read_char,
							   string& destination_state,
							   char& write_character,
							   Direction& move_direction);

	////////////////////////////////////////////
	//returns true if the given state is a source state for a transition
	////////////////////////////////////////////
	bool is_source_state(string state) const;
	
private:
	vector<Transition> transitions;
};

#endif /* defined(__tm__transition_function__) */
