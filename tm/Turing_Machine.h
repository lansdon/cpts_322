//
//  Turing_Machine.h
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

#ifndef __tm__Turing_Machine__
#define __tm__Turing_Machine__

#include <iostream>
#include <vector>

// Components
#include <sstream>
#include "Final_States.h"
#include "Input_Alphabet.h"
#include "States.h"
#include "Tape.h"
#include "Tape_Alphabet.h"
#include "Transition.h"
#include "Transition_Function.h"
#include "Uppercase.h"

using namespace std;

class Turing_Machine
{
public:
	/////////////////////////////////////////////////
	/*
	 o	Constructor. Takes a string argument which is the general 
	 name of the definition Turing Machine Definition without any 
	 file extensions. Both the definition file and the input string 
	 file must have this same exact name with .def and .str extensions respectively.
	 */
	/////////////////////////////////////////////////
	Turing_Machine(string definition_filename);
	
	bool parseDescription(ifstream& file);
	/////////////////////////////////////////////////
	//o	Loads definition file and calls load for every component.
	/////////////////////////////////////////////////
	bool loadDefinition(string filename);
	
	/////////////////////////////////////////////////
	// o	displays the TM definition in the console
	/////////////////////////////////////////////////
	void view_definition() const;
	
	/////////////////////////////////////////////////
	// o	Displays the id in the console formatted with the cells
	// left of the tape head followed by the current state and
	// lastly the current cell and cells to the right of the tape head.
	/////////////////////////////////////////////////
	void view_instantaneous_description(unsigned long maximum_number_of_cells) const;

	/////////////////////////////////////////////////
	// Initialize TM with given input string
	/////////////////////////////////////////////////
	void initialize(string input_string);
	
	/////////////////////////////////////////////////
	/*
	 o	This is the main operation of the TM. The TM will perform 
	 transitions on the current TM definition, up to the max_number_of_transitions. 
	 During this operation, the input string may be rejected if an error occurs, 
	 may be accepted if a final state is reached, or simply finish the 
	 max_number_of_transitions and stop.
	 */
	/////////////////////////////////////////////////
	void perform_transitions(unsigned long maximum_number_of_transitions);
	
	/////////////////////////////////////////////////
	// o	The user can opt to terminate operation without reaching conclusive condition.
	/////////////////////////////////////////////////
	void terminate_operation();
	
	/////////////////////////////////////////////////
	// o	Returns the current input string
	/////////////////////////////////////////////////
	string input_string() const;
	
	/////////////////////////////////////////////////
	// o	Returns the current number of transitions that have been performed.
	/////////////////////////////////////////////////
	int total_number_of_transitions() const;
	
	/////////////////////////////////////////////////
	// o	Returns true if the definition loaded from file is valid.
	/////////////////////////////////////////////////
	bool is_valid_definition() const;
	
	/////////////////////////////////////////////////
	//o	Returns true if the input_string is valid.
	/////////////////////////////////////////////////
	bool is_valid_input_string(string value) const;
	
	/////////////////////////////////////////////////
	//o	Returns true if  the TM has finished running on a string
	/////////////////////////////////////////////////
	bool is_used() const { return used; };
	
	/////////////////////////////////////////////////
	//o	Returns true if TM is currently running on a string
	/////////////////////////////////////////////////
	bool is_operating() const { return operating; };
	
	/////////////////////////////////////////////////
	//o	Returns true if the input string has been accepted
	/////////////////////////////////////////////////
	bool is_accepted_input_string() const { return accepted; };
	
	/////////////////////////////////////////////////
	//o	Returns true if the input string was rejected
	/////////////////////////////////////////////////
	bool is_rejected_input_string() const { return rejected; };
	
private:
	// Components
	Tape tape;
	Final_States final_states;
	Input_Alphabet input_alphabet;
	States states;
	Tape_Alphabet tape_alphabet;
	Transition_Function transition_function;
	
	// TM Variables
	vector<std::string> description; // a vector of strings (lines) representing the description of the Turing Machine Definition
	string initial_state; //	the initial state of the current definition
	string current_state; //	The current state of the TM
	string original_input_string; //	The original input string. A reference is kept in case the input string is accepted and the original string needs to be displayed.
	int number_of_transitions; //	The number of transitions that have been performed.
	bool valid;		//	The current validity of the TM based on transitions performed.
	bool used;		//	Determines if TM has finished on a string
	bool operating; //	True when TM is running on a string
	bool accepted;  //	True if the input string was accepted
	bool rejected;  //	True if the input string was rejected
	

};

#endif /* defined(__tm__Turing_Machine__) */
