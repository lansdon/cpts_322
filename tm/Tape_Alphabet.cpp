//
//  Tape_Alphabet.cpp
//  tm
//
//	Represents the legal tape alphabet
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Tape_Alphabet.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Uppercase.h"
using namespace std;


/////////////////////////////////////
// Loads the tape alphabet from the given
// definition file and sets valid to true if it was successful, else false.
/////////////////////////////////////
void Tape_Alphabet::load(ifstream& definition, bool& valid) {
	bool next_keyword_found = false;
	while(definition.good() && !next_keyword_found && valid) {
		string temp_char;
		if(!(definition >> temp_char)) {
			valid = false;
			cout << "Error reading tape alphabet.\n";
		} else {
			if(uppercase(temp_char) != "TRANSITION_FUNCTION:") {
				if((temp_char.length() == 1) &&
				   (temp_char[0] != '\\') &&
				   (temp_char[0] != '<') &&
				   (temp_char[0] != ']')) {
					alphabet.push_back(temp_char[0]);
				} else {
					cout << "Illegal Tape Character.\n";
					valid = false;
				}
			} else {
				next_keyword_found = true;		// TRANSITION_FUNCTION: found.
			}
		}
	} // end while loop
}



/////////////////////////////////////
// displays the current tape alphabet
/////////////////////////////////////
void Tape_Alphabet::view() const {
	stringstream msg;
	msg << "Tape alphabet = {";
	for(int i=0; i<alphabet.size(); ++i) {
		if(i>0) msg << ", ";
		msg << alphabet[i];
	}
	msg << "}\n";
	cout << msg.str();
}




/////////////////////////////////////
// Returns true if value is found in the current tape alphabet.
/////////////////////////////////////
bool Tape_Alphabet::is_element(char val) const {
	vector<char>::const_iterator it = alphabet.begin();
	while(it != alphabet.end()) {
		if(val == *it) return true;
		++it;
	}
	return false;
}
