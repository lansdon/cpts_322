//
//  States.cpp
//  tm
//
//  Created by Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "States.h"
#include "string_pointer.h"
#include "Uppercase.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//int States::number_of_states = 0;


/////////////////////////////////////
// Loads the states from the given definition file and sets valid to true if it was successful, else false.
/////////////////////////////////////
void States::load(ifstream& definition, bool& valid) {
	bool next_keyword_found = false;
	while(definition.good() && !next_keyword_found && valid) {
		string temp_state;
		if(definition >> temp_state) {
			if(uppercase(temp_state) != "INPUT_ALPHABET:") {		// prior to INPUT_ALPHABET: keyword
				states.push_back(temp_state);
			} else {
				next_keyword_found = true;		// INPUT_ALPHABET: found.
			}
		} else {
			cout << "Error reading states from definition file.\n";
			valid = false;
		}
	} // end while loop
}

/////////////////////////////////////
// displays the current set of states
/////////////////////////////////////
void States::view() const {
	stringstream msg;
	msg << "States = {";
	for(int i=0; i<states.size(); ++i) {
		if(i>0) msg << ", ";
		msg << states[i];
	}
	msg << "}\n";
	cout << msg.str();
}

/////////////////////////////////////
// Returns true if value is found in the set of states.
/////////////////////////////////////
bool States::is_element(string value) {
	vector<string>::iterator it = states.begin();
	while(it != states.end()) {
		if(value == *it) return true;
		++it;
	}
	return false;	
}
