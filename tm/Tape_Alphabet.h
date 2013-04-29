//
//  Tape_Alphabet.h
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

#ifndef __tm__Tape_Alphabet__
#define __tm__Tape_Alphabet__

#include <vector>
#include <fstream>
using namespace std;

class Tape_Alphabet
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
	
	
private:
	vector<char> alphabet;
	
};



#endif /* defined(__tm__Tape_Alphabet__) */
