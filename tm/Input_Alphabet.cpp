//
//  Input_Alphabet.cpp
//  tm
//
//This class represents the Input Alphabet which is the set of characters that are valid for an input string. This is a subset of the Tape Alphabet and excludes at minimum, the blank character.
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Input_Alphabet.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Uppercase.h"
using namespace std;



/////////////////////////////////////
// Loads the tape alphabet from the given definition file and sets valid to true if it was successful, else false.
/////////////////////////////////////
void Input_Alphabet::load(ifstream& definition, bool& valid) {
	bool next_keyword_found = false;
	while(definition.good() && !next_keyword_found && valid) {
		string temp_char;
		if(!(definition >> temp_char)) {
			valid = false;
			cout << "Error reading input alphabet.\n";
		} else {
			if(uppercase(temp_char) != "TAPE_ALPHABET:") {
				if((temp_char.length() == 1) &&
				   (temp_char[0] != '\\') &&
				   (temp_char[0] != '<') &&
				   (temp_char[0] != ']')) {
					alphabet.push_back(temp_char[0]);
				} else {
					cout << "Illegal Tape Alphabet Character.\n";
					valid = false;
				}
			} else {
				next_keyword_found = true;		// TAPE_ALPHABET: found.
			}
		}
	} // end while loop
}



/////////////////////////////////////
// displays the current tape alphabet
/////////////////////////////////////
void Input_Alphabet::view() const {
	stringstream msg;
	msg << "Input alphabet = {";
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
bool Input_Alphabet::is_element(char val) const {
	vector<char>::const_iterator it = alphabet.begin();
	while(it != alphabet.end()) {
		if(val == *it) return true;
		++it;
	}
	return false;
}




/////////////////////////////////////
// Returns the character at the specified index
/////////////////////////////////////
char Input_Alphabet::element(unsigned long index) const {
	if(index < alphabet.size()) {
		return alphabet[index];
	}
	return '/';  // error
}



