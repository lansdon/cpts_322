//
//  Turing_Machine.h
//  tm
//
//  Created by Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__Turing_Machine__
#define __tm__Turing_Machine__

#include <iostream>
#include <vector>

// Components
#include "Final_States.h"
#include "Input_Alphabet.h"
#include "States.h"
#include "Tape.h"
#include "Tape_Alphabet.h"
#include "Transition.h"
#include "Transition_Function.h"

using namespace std;

class Turing_Machine
{
public:
	Turing_Machine(string definition_filename);
	bool loadDefinition(string filename);
	void view_definition() const;
	void view_instantaneous_description(unsigned long maximum_number_of_cells) const;
	void initialize(string input_string);
	void perform_transitions(unsigned long maximum_number_of_transitions);
	void terminate_operation();
	string input_string() const;
	int total_number_of_transitions() const;
	bool is_valid_definition() const;
	bool is_valid_input_string(string value) const;
	bool is_used() const { return used; };
	bool is_operating() const { return operating; };
	bool is_accepted_input_string() const { return accepted; };
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
	vector<std::string> description;
	string initial_state;
	string current_state;
	string original_input_string;
	int number_of_transitions;
	bool valid;
	bool used;
	bool operating;
	bool accepted;
	bool rejected;
	

};

#endif /* defined(__tm__Turing_Machine__) */
