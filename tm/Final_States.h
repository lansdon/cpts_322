//
//  Final_States.h
//  tm
//
//  Created by Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__Final_States__
#define __tm__Final_States__

#include <string>
#include <vector>
using namespace std;

class Final_States
{
public:
	/////////////////////////////////////
	// Loads the final states from the given definition file and sets valid to true if it was successful, else false.
	/////////////////////////////////////
	void load(ifstream& definition, bool& valid);
	
	/////////////////////////////////////
	// displays the current set of final states
	/////////////////////////////////////
	void view() const;
	
	/////////////////////////////////////
	// Returns true if value is found in the set of final states.
	/////////////////////////////////////
	bool is_element(string value);

	/////////////////////////////////////
	// return number of final states
	/////////////////////////////////////
	int size() { return (int)final_states.size(); }
	
	/////////////////////////////////////
	// Returns true if value is found in the set of final states.
	/////////////////////////////////////
	string element(unsigned long index);
		
	
private:
	vector<string> final_states;
	
};


#endif /* defined(__tm__Final_States__) */
