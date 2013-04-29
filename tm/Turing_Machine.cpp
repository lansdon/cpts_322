//
//  Turing_Machine.cpp
//  tm
//
//	The delegate turing machine object that
// contains all components and handles
// delegation of tasks
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Turing_Machine.h"
#include <sstream>
#include "Final_States.h"
#include "Input_Alphabet.h"
#include "States.h"
#include "Tape.h"
#include "Tape_Alphabet.h"
#include "Transition.h"
#include "Transition_Function.h"
#include "Uppercase.h"



///////////////////////////////////
// Constructor. Takes a string argument which is the general name of
// the definition Turing Machine Definition without any file extensions.
// Both the definition file and the input string file must have this same
// exact name with .def and .str extensions respectively.
///////////////////////////////////
Turing_Machine::Turing_Machine(string definition_filename) :
	initial_state(""),
	current_state(""),
	original_input_string(""),
	number_of_transitions(0),
	valid(false),
	used(false),
	operating(false),
	accepted(false),
	rejected(false)
{
	if(loadDefinition(definition_filename)) {
		// Additional Setup
		

	} else {
		exit(1);
	}
}


///////////////////////////////////////////
// Utility function for extracting description
// - Maintains whitespace
/////////////////////////////////////////////
bool Turing_Machine::parseDescription(ifstream& definition_file) {
	unsigned long keyword_start = string::npos;
	bool description_complete = false;
	bool valid = true;
	
	// Extracting lines for description
	while(definition_file.good() && !description_complete && valid) {
		string line = "";
		if(getline(definition_file,line)) {				// extract a string
			
			string upper_line = uppercase(line);
			string final_line = "";
			
			keyword_start = upper_line.find(" STATES:");

			// search for first VALID keyword.
			while(keyword_start != string::npos && !description_complete) {
				string desc_substr = line.substr(0, keyword_start);
				string keyword = line.substr(keyword_start+1, 7);
				string rest_of_line = line.substr(keyword_start+8, string::npos);
				
				// Valid keyword found in the middle of the line with proper white space surrounding it
				if((rest_of_line.length() > 0 && rest_of_line[0] == ' ' ) ||
				   (rest_of_line.length() == 0) ) {
					final_line.append(desc_substr);
					
//					description.push_back(final_line);
					description_complete = true;
					
					// Put back reverse loop for rest_of_line here
					for(unsigned long i=rest_of_line.length(); i > 0; --i) {
						definition_file.unget();
					}
				} else {
					final_line.append(desc_substr);
					final_line.append(line.substr(keyword_start, 8));	// add false keyword with preceding space
					line = rest_of_line;
					upper_line = uppercase(rest_of_line);
				}
				keyword_start = upper_line.find(" STATES:");
			}

			if(final_line.length() > 0) {
				description.push_back(final_line);
			} else {
				description.push_back(line);
			}
	
		} else {
			cout << "Error reading description in definition file.\n";
			valid = false;
		}
	} // end while loop
	
	if(!description_complete) cout << "Error - STATES: keyword not found\n";
	
	return (valid && description_complete);
}


/////////////////////////////////////////////////
//o	Loads definition file and calls load for every component.
/////////////////////////////////////////////////
bool Turing_Machine::loadDefinition(string filename) {
	bool valid = true;
	
	// Load definition .def file
	stringstream def;
	def << filename<< ".def";
	ifstream definition_file(def.str().c_str());
	if(definition_file.is_open()) {
		// Extract header/description
		valid = parseDescription(definition_file);
/*
		bool description_complete = false;
		//	cout << "Loading description:\n";
		while(definition_file.good() && !description_complete && valid) {
			string temp;
			if(definition_file >> temp) {				// extract a string
				if(uppercase(temp) != "STATES:") {		// prior to STATES: keyword
					description.push_back(temp);
					//				cout << " " << temp;
				} else {
					description_complete = true;		// STATES: found.
					cout << endl;
				}
			} else {
				cout << "Error reading description in definition file.\n";
				valid = false;
			}
		} // end while loop
*/		
		// Now the header and STATES: keyword have been extracted. Continue
		// loading components:
		
		if(valid && !definition_file.eof())
			states.load(definition_file, valid);			// states
		else valid = false;
		
		if(valid && !definition_file.eof())
			input_alphabet.load(definition_file, valid);	// input alphabet
		else valid = false;
		
		if(valid && !definition_file.eof())
			tape_alphabet.load(definition_file, valid);		// tape alphabet
		else valid = false;
		
		if(valid && !definition_file.eof())
			transition_function.load(definition_file, valid);	// transition funct
		else valid = false;
		
		if(valid && !definition_file.eof()) {				// initial state
			string initial_state_temp;
			if(definition_file >> initial_state_temp && states.is_element(initial_state_temp)) {
				initial_state = initial_state_temp;
			} else {
				valid = false;
				cout << "Error reading initial state.\n";
			}
		}
		else valid = false;

		string blank_keyword;
		if(valid && !definition_file.eof() && definition_file >> blank_keyword && uppercase(blank_keyword) == "BLANK_CHARACTER:") {
			tape.load(definition_file, valid);			// blank char (tape)
		}
		else valid = false;
		
		if(valid && !definition_file.eof())
			final_states.load(definition_file, valid);	// final states
		else valid = false;
		
		definition_file.close();		
	} else {
		cout << "Error opening file...\n";
		valid = false;
	}
		
	if(valid) {
		cout << "TM Definition loaded successfully...\n";
	} else {
		cout << "TM Definition failed to load.\n";
	}

	return valid;
}






///////////////////////////////////
// displays the TM definition in the console
///////////////////////////////////
void Turing_Machine::view_definition() const {
	cout << "\n*********** TM Definition: **************\n";
	cout << "Description:\n";
	vector<string>::const_iterator it = description.begin();
	while(it!=description.end()) {
		cout << *it++ << endl;
	}
	cout << "*****************************************\n";
	states.view();
	input_alphabet.view();
	tape_alphabet.view();
	transition_function.view();
	cout << "Initial State = " << initial_state << endl;
	cout << "Blank Symbol = " << tape.blank_character() << endl;
	final_states.view();
	cout << "*****************************************\n";
	cout << endl << endl;
}

///////////////////////////////////
// displays the id in the console formatted with
// the cells left of the tape head followed by the current state and
// lastly the current cell and cells to the right of the tape
// head.
///////////////////////////////////
void Turing_Machine::view_instantaneous_description(unsigned long maximum_number_of_cells) const {
	cout << number_of_transitions << " " <<
			tape.left(maximum_number_of_cells) <<
			"[" << current_state << "]" <<
			tape.right(maximum_number_of_cells) << endl;
}

///////////////////////////////////
// Initializes TM with the passed input string
///////////////////////////////////
void Turing_Machine::initialize(string input_string) {
	if(is_valid_input_string(input_string)) {
		tape.initialize(input_string);
		original_input_string = input_string;
		number_of_transitions = 0;
		current_state = initial_state;
		valid = true;
		used = false;
		operating = true;
		accepted = false;
		rejected = false;		
	} else {
		cout << "Error - TM Initializated with invalid input string.\n";
	}
}


///////////////////////////////////
// This is the main operation of the TM.
// The TM will perform transitions on the current TM definition, up to
// the max_number_of_transitions. During this operation, the the input
// string may be rejected if an error occurs, may be accepted if a final
// state is reached, or simply finish the max_number_of_transitions and
// stop.
///////////////////////////////////
void Turing_Machine::perform_transitions(unsigned long maximum_number_of_transitions) {
	
	// Primary Loop - Max Iterations or Crash
	for(int i=0; i<maximum_number_of_transitions; ++i) {
//		cout << "perform transition:" << i << endl;
		// Search for transition
		if(transition_function.is_source_state(current_state)) {
			for(int transition=0; transition < transition_function.size(); ++transition) {
				if((transition_function.read_character(transition) == tape.current_character()) &&
				   (transition_function.source_state(transition) == current_state)) {
					// Found a transition!
					tape.update(transition_function.write_character(transition), transition_function.move_direction(transition));
					current_state = transition_function.destination_state(transition);
					++number_of_transitions;
					break;
				} else if (transition == transition_function.size()-1) {
					// No transition found !!
					// error no transition found
					rejected = true;
					accepted = false;
					operating = false;
					used = true;
				}
			}
		} else {
			// error no transition found
			rejected = true;
			accepted = false;
			operating = false;
			used = true;
			break;
		}

		if(final_states.is_element(current_state)) {
			// WIN!
			cout << "Success - Input string accepted.\n";
			rejected = false;
			accepted = true;
			operating = false;
			used = true;
			break;
		} else if (!operating) {
			cout << "CRASH - No transition found.\n";
			break;
		}
	}
}

///////////////////////////////////
// The user can opt to terminate operation without reaching conclusive
// condition.
///////////////////////////////////
void Turing_Machine::terminate_operation() {
	cout << "Input string " << original_input_string << " not accepted or rejected in " << number_of_transitions << " transitions\n";
	operating = false;
	accepted = false;
	rejected = false;
	used = true;
}

///////////////////////////////////
// Returns the current input string
///////////////////////////////////
string Turing_Machine::input_string() const {
	return original_input_string;
}

///////////////////////////////////
// Returns the current number of transitions that have been performed.
///////////////////////////////////
int Turing_Machine::total_number_of_transitions() const {
	return number_of_transitions;
}

///////////////////////////////////
// Returns true if the input_string is valid.
///////////////////////////////////
bool Turing_Machine::is_valid_input_string(string value) const {
	string::iterator it = value.begin();
	while(it != value.end()) {
		if(!input_alphabet.is_element(*it)) {
			return false;
		}
		++it;
	}
	return true;
}

///////////////////////////////////
// Run a validation algorithm on loaded TM
///////////////////////////////////
bool Turing_Machine::is_valid_definition() const {
	
	// input alphabet is subset of tape alphabet
	for(int i=0; i<input_alphabet.size(); ++i) {
		if(!tape_alphabet.is_element( input_alphabet.element(i))) {
			cout << "Invalid definition - Input alphabet is not a subset of tape alphabet.\n";
			return false;
		}
	}
	
	// blank char is in tape alphabet and not in input alphabet
	if(!(tape_alphabet.is_element(tape.blank_character()) && !input_alphabet.is_element(tape.blank_character()))) {
		cout << "Invalid definition - Blank char cannot be part of input alphabet and must be part of the tape alphabet.\n";
		return false;
	}
	
	// No transition out of final states
	for(int i=0; i<final_states.size(); ++i) {
		if(transition_function.is_source_state(final_states.element(i))) {
			cout << "Invalid definition - Final states cannot be source states for transitions.\n";
			return false;
		}
		// Final states - must be subset of states
		if(!states.is_element(final_states.element(i))) {
			cout << "Invalid definition - Final states must be subset of States\n";
			return false;
		}
	}
	
	// Transition states must exist in states
	for(int i=0; i < transition_function.size();++i) {
		if(!(states.is_element(transition_function.source_state(i)) && states.is_element(transition_function.destination_state(i)))) {
			cout << "Invalid definition - Transition function source and destination states must exist in States\n";
			return false;
		}
		// validate transition read/write chars as subset of tape alphabet
		if(!(tape_alphabet.is_element(transition_function.read_character(i))) &&
		   (tape_alphabet.is_element(transition_function.write_character(i)))) {
			cout << "Invalid definition - Transition function source and destination states must exist in States\n";
			return false;
		}
	}
	
	// initial state is in states
	if(!states.is_element(initial_state)) {
		cout << "Invalid definition - Initial state must exist in States\n";
		return false;
	}
	
	// Blank char not in input alphabet
	if(input_alphabet.is_element(tape.blank_character())) {
		cout << "Invalid definition - Blank char cannot be in input alphabet\n";
		return false;
	}
	
	
	return true;	// Passed all the tests!
};
