//
//  Transition_Function.cpp
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

#include "Transition_Function.h"

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

////////////////////////////////////////////
// Loads the transitions from the definition_file. Sets valid to true on success, else false.
////////////////////////////////////////////
void Transition_Function::load(ifstream& definition, bool& valid) {
	bool next_keyword_found = false;
	while(definition.good() && !next_keyword_found && valid) {
		string source, current_char, dest, write, move;
		
		// check for next keyword first
		if(definition >> source) {
			if(uppercase(source) == "INITIAL_STATE:") {
				next_keyword_found = true;
				break;
			}
		} else {
			valid = false;
			cout << "Error reading transition.\n";
		}

		
		if(!((definition >> current_char) &&
			 (definition >> dest) &&
			 (definition >> write) &&
			 (definition >> move))) {
			valid = false;
			cout << "Error reading transition.\n";
		} else {
			if((uppercase(current_char) != "INITIAL_STATE:") &&
			   (uppercase(dest) != "INITIAL_STATE:") &&
			   (uppercase(write) != "INITIAL_STATE:") &&
			   (uppercase(move) != "INITIAL_STATE:") &&
			   (current_char.length() == 1) &&
			   (write.length() == 1) &&
			   (move.length() == 1) &&
			   (uppercase(move)[0] == 'L' || uppercase(move)[0] == 'R')) {
				transitions.push_back(Transition(source, current_char[0], dest, write[0], move[0]));
			} else {
				cout << "Invalid transition found.\n";
				valid = false;
			}
		}
	} // end while loop
	
}



////////////////////////////////////////////
//	Displays the loaded transitions
////////////////////////////////////////////
void Transition_Function::view() const {
	stringstream msg;
	msg << "\n----- Loaded Transitions: -----\n";
	vector<Transition>::const_iterator it = transitions.begin();
	while(it != transitions.end()) {
		msg << "Transition(" <<
		it->source_state() << ", " <<
		it->read_character() << ") = (" <<
		it->destination_state() << ", " <<
		it->write_character() << ", " <<
		it->move_direction() << ")\n";
		++it;
	}
	cout << msg.str() << endl;
}



////////////////////////////////////////////
// Returns the number of stored transitions
////////////////////////////////////////////
int Transition_Function::size() const {
	return (int)transitions.size();
}


////////////////////////////////////////////
// return source state
////////////////////////////////////////////
string Transition_Function::source_state(unsigned long index) const {
	return transitions[index].source_state();
}


////////////////////////////////////////////
// return read char
////////////////////////////////////////////
char Transition_Function::read_character(unsigned long index) const {
	return transitions[index].read_character();
}



////////////////////////////////////////////
// return detination state
////////////////////////////////////////////
string Transition_Function::destination_state(unsigned long index) const {
	return transitions[index].destination_state();
}



////////////////////////////////////////////
// write char of given transition
////////////////////////////////////////////
char Transition_Function::write_character(unsigned long index) const {
	return transitions[index].write_character();
}

////////////////////////////////////////////
// move direction of given transition
////////////////////////////////////////////
Direction Transition_Function::move_direction(unsigned long index) const {
	return transitions[index].move_direction();
}


////////////////////////////////////////////
// Find a matching saved transition
////////////////////////////////////////////
bool Transition_Function::is_defined_transition(string source_state,
						   char read_char,
						   string& destination_state,
						   char& write_character,
						   Direction& move_direction)
{
	for(int i=0; i<transitions.size(); ++i) {
		if((transitions[i].source_state() == source_state) &&
		   (transitions[i].read_character() == read_char)) {
			destination_state = transitions[i].destination_state();
			write_character = transitions[i].write_character();
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////
//returns true if the given state is a source state for a transition
////////////////////////////////////////////
bool Transition_Function::is_source_state(string state) const {
	std::vector<Transition>::const_iterator it = transitions.begin();
	while(it != transitions.end()) {
		if(state == it->source_state()) {
			return true;
		}
		++it;
	}
	return false;
}
