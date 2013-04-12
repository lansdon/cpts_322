//
//  transition_function.h
//  tm
//
//  Created by Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__transition_function__
#define __tm__transition_function__

#include <iostream>
#include "Transition.h"
#include "Direction.h"
#include <string>
#include <vector>
#include <fstream>
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
	string source_state(unsigned long index);
	char read_character(unsigned long index) const;
	string destination_state(unsigned long index) const;
	char write_character(unsigned long index) const;
	Direction move_direction(unsigned long index) const;
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
