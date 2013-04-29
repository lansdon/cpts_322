//
//  Tape.cpp
//  tm
//
//	Represents the tape component of the Turing Machine
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Tape.h"

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "Direction.h"
#include "Uppercase.h"

//#include "Crash.h"

using namespace std;

Tape::Tape():
	cells(" "),
	current_cell(0),
	blank(' ')
{
}

void Tape::load(ifstream& definition, bool& valid) {
	std::string value;
	if((definition >> value) &&
	   (value.length() == 1) && (value[0] != '\\') &&
	   (value[0] != '<') && (value[0] != ']') &&
	   (value[0] >= '!') && (value[0] <= '~')) {
		blank = value[0];
	} else {
		cout << "Illegal Blank Character.\n";
		valid = false;
	}

	if((!(definition >> value)) ||
	   (uppercase(value) != "FINAL_STATES:")) {
		cout << "Missing keyword after blank character.\n";
		valid = false;
	}
	
}

void Tape::view() const {
	cout << "B =  " << blank << "\n\n";
}

void Tape::initialize(string input_string) {
	cells = input_string + blank;
	current_cell = 0;
}

void Tape::update(char write_character, Direction move_direction) {
	move_direction = uppercase(move_direction);
	if((move_direction == 'L') && (current_cell == 0)) {
		throw runtime_error("Left move from first cell");
	}

	if((move_direction == 'R') &&
	   (current_cell == cells.length()-1)) {
		cells += blank;
	}
	cells[current_cell] = write_character;
	
	if(move_direction == 'L') --current_cell;
	else ++current_cell;
	
}

string Tape::left(unsigned long maximum_number_of_cells) const {
	int first_cell = max(0, current_cell - (int)maximum_number_of_cells);
	string value = cells.substr(first_cell, current_cell-first_cell);
	if(value.length() < current_cell) {
		value.insert(0, "<");
	}
	return value;
}

string Tape::right(unsigned long maximum_number_of_cells) const {
	int end_cell = (int)cells.length();
	while((end_cell >= current_cell) &&
		  (cells[end_cell] == blank)) {
		--end_cell;
	}
	int last_cell = min(end_cell, current_cell+(int)maximum_number_of_cells-1);
	string value = cells.substr(current_cell, last_cell-current_cell+1);
	if(value.length() < (end_cell-current_cell)) {
		value.append(">");
	}
	return value;
}


