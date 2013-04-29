//
//  Menu.cpp
//  tm
//
// This menu system is the application UI and drives
// the entire program. Handles all user input.
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 4/11/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include "Menu.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <climits>
#include "Turing_Machine.h"
#include "Uppercase.h"
using namespace std;

// Constructor
Menu::Menu(app_configuration* cfg, Turing_Machine* turing_machine) :
	config(cfg),
	tm(turing_machine),
	save_input_strings_on_exit(false)
{
	loadInputStrings(cfg->FILENAME_BASE);	
}


// runs the menu system
bool Menu::menuLoop() {
	displayMenu();
	return processUserCommand();
}


bool Menu::processUserCommand() {
//	cout << setfill('_') << setw(20) << "" << setfill(' ') << endl;
	std::cout << "Command:";
	string cmd;
	getline(cin, cmd);
	
	if(cmd.length() > 1) {
		cout << "Invalid selection\n";	// multiple chars is illegal
		return processUserCommand();
	} else if(cmd.length() == 1) {		// Single char selected, try to resolve.
		switch(uppercase(cmd)[0]) {
			case 'D': delete_string(); break;
			case 'E': set(); break;
			case 'H': help(); break;
			case 'I': insert(); break;
			case 'L': list(); break;
			case 'Q': quit(); break;
			case 'R': run(); break;
			case 'T': truncate(); break;
			case 'V': view(); break;
			case 'W': show(); break;
			case 'X': exit(); break;
			default:
				cout << "Invalid selection\n";		// error
				return processUserCommand();
		}
	} else if (cmd.length() == 0) {		// No chars, display command line again
		return processUserCommand();
	}
	return true;
}


bool Menu::displayMenu() {
	if (config->HELP_ON) {
		std::cout << "\n";
		std::cout << "Turing Machine - Menu\n";
		std::cout << "(H)elp - Displays details about commands\n";
		std::cout << "(D)elete - Delete an input string by number\n";
		std::cout << "E(x)it - Exit the program\n";
		std::cout << "(I)nsert - Append a new input string to the list of input strings\n";
		std::cout << "(L)ist - Display list of input strings\n";
		std::cout << "(Q)uit - Stop the Turing Machine operation\n";
		std::cout << "(R)un - Run the Turing Machine on the chosen input string. Prompted for a string selection if there isn't an active input string.\n";
		std::cout << "S(e)t - Set maximum number of transitions to perform in one pass using run command.\n";
		std::cout << "Sho(w) - About this app\n";
		std::cout << "(T)runcate - Set MAX number of chars per side in ID\n";
		std::cout << "(V)iew - Show the current TM Definition\n";
	} else {
/*
		std::cout << "\n";
		std::cout << "Turing Machine - Menu\n";
		std::cout << "(H)elp\n";
		std::cout << "(D)elete\n";
		std::cout << "E(x)it\n";
		std::cout << "(I)nsert\n";
		std::cout << "(L)ist\n";
		std::cout << "(Q)uit\n";
		std::cout << "(R)un\n";
		std::cout << "S(e)t\n";
		std::cout << "Sho(w)\n";
		std::cout << "(T)runcate\n";
		std::cout << "(V)iew\n";
 */
	}
	return true;
}



bool Menu::loadInputStrings(string filename) {
	// Load definition .def file
	stringstream def;
	def << filename<< ".str";
	ifstream string_file(def.str().c_str());
	if(! string_file.is_open()) {
		cout << "Error opening input string file...\n";
		return false;
	}
	
	while (string_file.good()) {
		string line;
		getline(string_file, line);
		if(tm->is_valid_input_string(line)) {
			input_strings.push_back(line);
			//		cout << "Input string: " << line << endl;
		} else {
			cout << "- Invalid input string ignored (\"" << line << "\")\n";
		}
	}
	string_file.close();
	
	cout << "Input String File loaded successfully...\n";
	return true;
}



/*
 (D)elete
 Delete input string from list (one at a time)
 will cause no gap in list. (remove object from list)
 indicating by number
 errors for invalid input
 on success - output validating message
 ENTER = no error, back to main menu
 */
void Menu::delete_string() {
	cout << "Delete input string[";
	input_strings.size() ?	cout << "1-" << input_strings.size() :
	cout << "None available";
	cout << "]: ";
	string input_string;
	std::getline(cin, input_string);
	unsigned long index = atol(input_string.c_str());
	if(input_strings.size() && index > 0 && input_string.length() == numDigits(index) && index <= input_strings.size() ) {
		input_strings.erase(input_strings.begin()+index-1);
		save_input_strings_on_exit = true;
		cout << "\nInput string deleted. (save file queued)\n";
	} else {
		if(input_string.length())
			cout << "\nError - Invalid selection. " << "\n";
	}
}


/*
 S(e)t
 Set maximum number of transitions to perform
 ex: "Maximum number of transitions[1]: "
 should display current value as part of prompt
 carriage return = NO MSG. back to menu prompt
 must be >= 1,    0 = error!
*/
bool Menu::set() {
	cout << "Maximum number of transitions[" << config->MAX_TRANSITIONS << "]: ";
	string input_string;
	std::getline(cin, input_string);
	unsigned long new_value = atol(input_string.c_str());
	if(input_string.length() == numDigits(new_value) && new_value > 0) {
		config->MAX_TRANSITIONS = new_value;
		cout << "\nMax transitions changed.\n";
		return true;
	}
	if(input_string.length())
		cout << "\nError - Max transitions must be a integer from 1 to " << LONG_MAX << "\n";

	return false;
}


/*
 (H)elp
 Help User with prompts or not
 change setting for whether or not help messages are 
 provided to user for all prompts input
 defaults to NO.    Toggles yes or no
 */
void Menu::help() {
	config->HELP_ON = !(config->HELP_ON);
}


/*
 (I)nsert
 Insert input string into the list from Sigma* and 
 append it to list of input strings
 Prompt for input string    "Input string: "
 if string is duplicate of existing string or contains 
 an illegal character -> display appropriate error message
*/
void Menu::insert() {
	cout << "Input string:";
	string input_string;
	std::getline(cin, input_string);
	
	// Search for duplicate strings
	vector<string>::iterator it;
	for(it=input_strings.begin();it!=input_strings.end();++it) {
		if(input_string == *it) {
			cout << "That string already exists in the list.\n";
			return;
		}
	}
	
	// Validate string and add it.
	if(tm->is_valid_input_string(input_string)) {
		input_strings.push_back(input_string);
		save_input_strings_on_exit = true;
		cout << "\nInput string saved. (save file queued)\n";
	} else {
		cout << "\nError - Invalid input string.\n";
	}
}


/*
 (L)ist
 List input strings
 each string on its own line
 each string numbered sequentially starting with 1
 Empty list displays message
 Empty string shown as backslash
 No error if no string is entered.. go back to prompt
 \  is used to input blank string
*/
void Menu::list() {
	cout << "\nInput Strings:\n";
	
	// empty list message
	if(input_strings.size() == 0) {
		cout << "<No input strings loaded>\n";
		return;
	}
	
	// Display strings
	for(int i=0; i<input_strings.size(); ++i) {
		if(input_strings[i].size()) {
			cout << i+1 << ") " << input_strings[i] << endl;
		} else {
			cout << i+1 << ") \\" << endl;
		}
	}
	cout << endl;
}


/*
 (Q)uit
 Quit operation of ™ on input string before completion
 "Input string AABBAA not accepted or rejected in 200 transitions"
 Error if no string is selected
*/
void Menu::quit() {
	if(tm->input_string().length() > 0) {
		tm->terminate_operation();
	} else {
		// error no string
		cout << "Error - No input string selected.\n";
	}
}


/*
 ( R )un
 Run ™ on input string
 prompts for input string if it's not running (including done w/ old string)
 if running, perform next set of transitions
 example:
 command: R
 Input string #: 5
 0 [S0]AABBABBAAA>      (INITIAL ID IS DISPLAYED)
 100. <BXAABYAAAB[s3]XYYABBAABYY>
 command R
 200. ABYX[S2]ABBB
 command: R
 225 ABYX[s5]AX
 Input string   AAABBBBABB accepted in 225 transitions
 command: 
*/
void Menu::run() {
	
	// Select Input String
	if(!tm->is_operating()) {
		cout << "Input String:[";
		input_strings.size() ?	cout << "1-" << input_strings.size() :
								cout << "None available";
		cout << "]: ";
		string input_string;
		std::getline(cin, input_string);
		unsigned long index = atol(input_string.c_str());
		if(input_strings.size() && index > 0 && input_string.length() == numDigits(index) && index <= input_strings.size() ) {
			tm->initialize(input_strings[index-1]);			
			tm->view_instantaneous_description(config->MAX_ID_CHARS);
		} else {
			if(input_string.length())
				cout << "\nError - Invalid selection. " << "\n";
			return;
		}
	}	
	tm->perform_transitions(config->MAX_TRANSITIONS);
	tm->view_instantaneous_description(config->MAX_ID_CHARS);
}


/*
 (T)runcate
 Truncate instantaneous descriptions
 command allows user to change setting for max 
 number of chars to left and right of tape head to 
 display in ID during operation of ™ input string
 same rules as SET  (positive ints > 0, same errors)
 */
bool Menu::truncate() {
	cout << "Maximum ID chars per side[" << config->MAX_ID_CHARS << "]: ";
	string input_string;
	std::getline(cin, input_string);
	unsigned long new_value = atol(input_string.c_str());
	if(input_string.length() == numDigits(new_value) && new_value > 0) {
		config->MAX_ID_CHARS = new_value;
		cout << "\nMax ID chars changed.\n";
		return true;
	}
	if(input_string.length())
		cout << "\nError - Max ID chars must be a integer from 1 to " << LONG_MAX << "\n";
	return false;
}



/*
 (V)iew
 View turfing machine (states, transition function, etc)
 Definition of currently loaded machine in a form readable 
 to user (use curly braces, commas, etc etc) but don't 
 display .def file contents.
 Description of ™ from .def file (without alteration)
 Formal specification of ™ M=(Q, sigma, gamma, sigma, q_0, B, F)
 example transition: DELTA(s0, A) = (s1, B, R)
 Don't use keywords from .def file
 use notation from formal specification as much as 
 possible, including equal signs, parenthesis, comma, curly brackets, etc
 See turing machine specification paper handout
*/
void Menu::view() {
	tm->view_definition();
}

/*
 Sho(w)
 Show status of application
 Course, Semester,
 Year, Instructor,
 Author,
 version of application,
 configuration settings(3),
 name of ™ (without .def = the argument passed in),
 status of ™ (3),
 if ™ is currently running, display input string and total number of transitions,
 if ™ has completed operation on input string, display last input string used
 and if completed whether it was accepted, rejected, or terminated by user
 if completed total number of transitions performed.
 status information is not retained when we exit application
 NO ID's (instantaneous Description)
 no true or false… must be "yes or no"
 */
void Menu::show() {
	cout << endl;
	cout << "*********** About This App *************\n";
	cout <<left<< setw(20) << "Title:" << "Turing Machine\n";
	cout <<left<< setw(20) << "Author:" << "Lansdon Page\n";
	cout <<left<< setw(20) << "Course:" << "CPTS_322\n";
	cout <<left<< setw(20) << "Semester:" << "Spring 2013\n";
	cout <<left<< setw(20) << "Instructor:" << "Neil Corrigan\n";
	cout <<left<< setw(20) << "Version:" << "1.0\n";
	cout <<left<< setw(20) << "Settings:" << "\n";
	cout <<left<< setw(20) << "-- Max Transitions:" << config->MAX_TRANSITIONS << "\n";
	cout <<left<< setw(20) << "-- Max ID Chars:" << config->MAX_ID_CHARS << "\n";
	cout <<left<< setw(20) << "-- Help:" <<
	(config->HELP_ON ? "ON" : "OFF") << "\n";
	cout <<left<< setw(20) << "Current File:" << config->FILENAME_BASE << endl;
	cout <<left<< setw(20) << "TM -- Running:" <<
	(tm->is_operating() ? "YES" : "NO") << "\n";
	if(tm->is_operating()) {
		cout <<left<< setw(20) << "-- Input String:" << tm->input_string() << "\n";
		cout <<left<< setw(20) << "-- Total Transitions:" << tm->total_number_of_transitions() << "\n";
	}
	cout <<left<< setw(20) << "TM -- Used:" <<
	(tm->is_used() ? "YES" : "NO") << "\n";
	if(tm->is_used()) {
		if(tm->input_string().length() > 0) {
			cout <<left<< setw(20) << "-- Last Input String:" << tm->input_string() << "\n";
		} else {
			cout <<left<< setw(20) << "-- Last Input String: \\" << "\n";
		}
		cout <<left<< setw(20) << "-- Result:";
		if(tm->is_accepted_input_string()) {
			cout << "Accepted\n" <<left<<
			setw(20) << "Total Transitions:" << tm->total_number_of_transitions() << endl;
		}
		else if(tm->is_rejected_input_string()) cout << "Rejected\n";
		else cout << "Terminated\n";
	}

}


/*
 E(x)it
 Exit application
 No confirmation
 replace input string file if changes occurred using insert/delete.
 If writing file fails, print error message and quit
 on successfully writing file display success message
 */
void Menu::exit() {
	if(save_input_strings_on_exit) {
		// Save input string file .str
		stringstream def;
		def << config->FILENAME_BASE << ".str";
		ofstream string_file(def.str().c_str());
		if(! string_file.is_open()) {
			cout << "Error opening input string file...\n";
			std::exit(-1);
		}
		
		for(int i=0; i<input_strings.size(); ++i) {
			string_file << input_strings[i];
			if(i < input_strings.size()-1) string_file << endl;
		}
		cout << config->FILENAME_BASE << ".str updated successfully.\n";
		string_file.close();
	}
	std::exit(0);
}



