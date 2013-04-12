//
//  Tape.h
//  tm
//
//  Created by Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__Tape__
#define __tm__Tape__

// STL
#include <iostream>
#include <fstream>
#include <string>

// TM
#include "direction.h"

using namespace std;

class Tape
{
public:
	Tape();
	void load(ifstream& definition, bool& valid);
	void view() const;
	void initialize(string input_string);
	void update(char write_character, Direction move_direction);
	string left(unsigned long maximum_number_of_cells) const;
	string right(unsigned long maximum_number_of_cells) const;
	char current_character() const { return cells[current_cell]; };
	char blank_character() const { return blank; };
	bool is_first_cell() const { return (current_cell == 0); };	
	
private:
	string cells;
	int current_cell;
	char blank;
};


#endif /* defined(__tm__Tape__) */
