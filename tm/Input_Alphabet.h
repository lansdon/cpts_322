//
//  Input_Alphabet.h
//  tm
//This class represents the Input Alphabet which is the set of characters that are valid for an input string. This is a subset of the Tape Alphabet and excludes at minimum, the blank character.
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__Input_Alphabet__
#define __tm__Input_Alphabet__

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Uppercase.h"
using namespace std;


class Input_Alphabet
{

public:
	
	/////////////////////////////////////
	// Loads the tape alphabet from the given definition file and sets valid to true if it was successful, else false.
	/////////////////////////////////////
	void load(ifstream& definition, bool& valid);
	
	/////////////////////////////////////
	// displays the current tape alphabet
	/////////////////////////////////////
	void view() const;
	
	/////////////////////////////////////
	// Returns true if value is found in the current tape alphabet.
	/////////////////////////////////////
	bool is_element(char val) const;

	/////////////////////////////////////
	// Returns the character at the specified index
	/////////////////////////////////////
	char element(unsigned long index) const;
	
	/////////////////////////////////////
	// returns the number of characters in the input alphabet
	/////////////////////////////////////
	unsigned long size() const { return alphabet.size(); }
	
private:
	// A vector containing the set of characters that make up the input alphabet
	vector<char> alphabet;

};


#endif /* defined(__tm__Input_Alphabet__) */
