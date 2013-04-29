//
//  Final_States.cpp
//  tm
//
//	Represents the list of final states
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Final_States.h"

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Uppercase.h"
using namespace std;



/////////////////////////////////////
// Loads the final states from the given definition file and sets valid to true if it was successful, else false.
/////////////////////////////////////
void Final_States::load(ifstream& definition, bool& valid) {
	bool next_keyword_found = false;
	while(definition.good() && !next_keyword_found && valid) {
		string temp_state;
		if(definition >> temp_state) {
			if(uppercase(temp_state) != "INPUT_ALPHABET:") {		// prior to INPUT_ALPHABET: keyword
				final_states.push_back(temp_state);
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
// displays the current set of final states
/////////////////////////////////////
void Final_States::view() const{
	stringstream msg;
	msg << "Final States = {";
	for(int i=0; i<final_states.size(); ++i) {
		if(i>0) msg << ", ";
		msg << final_states[i];
	}
	msg << "}\n";	
	cout << msg.str();
}

/////////////////////////////////////
// Returns true if value is found in the set of final states.
/////////////////////////////////////
bool Final_States::is_element(string value) const {
	vector<string>::const_iterator it = final_states.begin();
	while(it != final_states.end()) {
		if(value == *it) return true;
		++it;
	}
	return false;	
}


/////////////////////////////////////
// Returns true if value is found in the set of final states.
/////////////////////////////////////
string Final_States::element(unsigned long index) const {
	if(index < final_states.size()) {
		return final_states[index];
	}
	return "FINAL STATES INDEX ERROR";
}
