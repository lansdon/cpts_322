//
//  Turing_Machine.cpp
//  tm
//
//  Created by Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Turing_Machine.h"
#include "Final_States.h"
#include "Input_Alphabet.h"
#include "States.h"
#include "Tape.h"
#include "Tape_Alphabet.h"
#include "Transition.h"
#include "Transition_Function.h"
#include <sstream>
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



bool Turing_Machine::loadDefinition(string filename) {
	bool valid = true;
	
	// Load definition .def file
	stringstream def;
	def << filename<< ".def";
	ifstream definition_file(def.str());
	if(! definition_file.is_open()) cout << "Error opening file...\n";

	// Extract header/description
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
	
	// Now the header and STATES: keyword have been extracted. Continue
	// loading components:
	
	if(valid && definition_file.good())
		states.load(definition_file, valid);			// states
	if(valid && definition_file.good())
		input_alphabet.load(definition_file, valid);	// input alphabet
	if(valid && definition_file.good())
		tape_alphabet.load(definition_file, valid);		// input alphabet
	if(valid && definition_file.good())
		transition_function.load(definition_file, valid);	// transition funct
	if(valid && definition_file.good()) {				// initial state
		string initial_state_temp;
		if(definition_file >> initial_state_temp && states.is_element(initial_state_temp)) {
			initial_state = initial_state_temp;
		} else {
			valid = false;
			cout << "Error reading initial state.\n";
		}
	}
	string blank_keyword;
	if(valid && definition_file.good() && definition_file >> blank_keyword && uppercase(blank_keyword) == "BLANK_CHARACTER:") {
		tape.load(definition_file, valid);			// blank char (tape)
	}
	if(valid && definition_file.good())
		final_states.load(definition_file, valid);	// final states
	
	definition_file.close();
	
	if(valid) {
		cout << "TM Definition loaded successfully.\n";
	} else {
		cout << "TM Definition failed to load.\n";
	}
	this->valid = valid;	// update valid status
	return valid;
}






///////////////////////////////////
// displays the TM definition in the console
///////////////////////////////////
void Turing_Machine::view_definition() const {
	cout << "\nTM Definition:\n";
	states.view();
	input_alphabet.view();
	tape_alphabet.view();
	transition_function.view();
	cout << "Initial State = " << initial_state << endl;
	cout << "Blank Symbol = " << tape.blank_character() << endl;
	final_states.view();
	cout << endl << endl;
}

///////////////////////////////////
// displays the id in the console formatted with
// the cells left of the tape head followed by the current state and
// lastly the current cell and cells to the right of the tape
// head.
///////////////////////////////////
void Turing_Machine::view_instantaneous_description(unsigned long maximum_number_of_cells) const {
	cout << "Instantaneous Description = " <<
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
		cout << "perform transition:" << i << endl;
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
				}
			}
		} else {
			// error no transition found
			cout << "CRASH - No transition found.\n";
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
		}
	}
}

///////////////////////////////////
// The user can opt to terminate operation without reaching conclusive
// condition.
///////////////////////////////////
void Turing_Machine::terminate_operation() {
	cout << "Input string " << original_input_string << " not accepted or rejected in " << number_of_transitions << "transitions\n";

//	cout << "TM Operation terminated with " << number_of_transitions << " transitions.\n";
	operating = false;
	accepted = false;
	rejected = false;
	used = true;
	// clear input string?
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
	return valid;
};
