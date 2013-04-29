//
//  Menu.h
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

#ifndef __tm__Menu__
#define __tm__Menu__

#include <string>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Turing_Machine.h"
#include "Uppercase.h"
using namespace std;


struct app_configuration {
	unsigned long MAX_TRANSITIONS;// = 1; // Max number of transitions to perform at a time (default 1)
	bool HELP_ON;// = false; // Whether or not help messages are provided to the user for all prompt:   default (NO messages)
	unsigned long MAX_ID_CHARS;// = 32;	// Max number of cells to the left and to the right of the tape head to display in instantaneous
	string FILENAME_BASE;// = "";
};

// generic solution
template <class T>
int numDigits(T number)
{
    int digits = 0;
//    if (number < 0) digits = 1; // remove this line if '-' counts as a digit
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
};


class Menu {
public:
	Menu(app_configuration* cfg, Turing_Machine* turing_machine);
	bool menuLoop();	// runs the menu system
	bool loadInputStrings(string filename);
private:
	app_configuration* config;	// pointer to application configuration
	Turing_Machine* tm;			// pointer to application tm
	vector<string> input_strings;
	bool save_input_strings_on_exit;
	
	// Display Prompt->Get Input->Run command
	bool processUserCommand();
	
	// Display menu
	bool displayMenu();
	
	// *******   Commands ********* //
	// delete
	void delete_string();
	// Set
	bool set();
	// Help
	void help();
	// Insert
	void insert();
	// List
	void list();
	// Quit
	void quit();
	// Run
	void run();
	// Truncate
	bool truncate();
	// view
	void view();
	// Show
	void show();
	// exit
	void exit();
};




#endif /* defined(__tm__Menu__) */
