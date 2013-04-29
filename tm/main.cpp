//
//  main.cpp
//  tm
//
// Program entry point. Instantiates and owns the Turing Machine object and Menu object
// Contains primary application loop
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include <iostream>
#include <exception>
#include <string>
#include <iostream>
#include <iomanip>

#include "Turing_Machine.h"
#include "Menu.h"

using namespace std;


int main(int argc, const char * argv[])
{
	const int success(0);

	// Acquire filename passed as argument
	string filename = "test";
	if (argc == 2) {
		filename = argv[1];
	} else {
		cout << "\nYou must pass a single filename argument.\nExample: <application> <filename>\n";
		exit(1);
	}
	
	// Setup configuration
	app_configuration* config = new app_configuration();
	config->HELP_ON = false;	// default (NO messages)
	config->MAX_TRANSITIONS = 1; // Max number of transitions to perform at a time (default 1)
	config->MAX_ID_CHARS = 32; // Max number of cells to the left and to the right of the tape head to display in instantaneous description. (default: 32 in each direction)
	config->FILENAME_BASE = filename;
	
//	cout << setfill('_') << setw(28) << "" << endl;
//	cout << "Hello, Turing Machine World!\n";
		
	// Load Turing Machine Object
	Turing_Machine tm(filename);

	// Validate loaded definition
	if (!tm.is_valid_definition()) {
		cout << "Invalid definition: Shutting down.\n";
		return -1;
	}
	
	// Load Menu System
	Menu menu(config, &tm);
	
	// Application Loop
	while (menu.menuLoop()) {
				
	}
	
	delete config;	// cleanup config object
    return success;
}



