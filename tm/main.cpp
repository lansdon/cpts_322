//
//  main.cpp
//  tm
//
//  Created by Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#include <iostream>
#include <exception>
#include <string>
#include <iostream>
#include <iomanip>

#include "Turing_Machine.h"
#include "Tape.h"
#include "Direction.h"
#include "Uppercase.h"
#include "Menu.h"

using namespace std;


/*
 Configuration Settings:
 */
int MAX_TRANSITIONS = 1; // Max number of transitions to perform at a time (default 1)
bool HELP_ON = false; // Whether or not help messages are provided to the user for all prompt:   default (NO messages)
int MAX_ID_CHARS = 32;	// Max number of cells to the left and to the right of the tape head to display in instantaneous description. (default: 32 in each direction)

int main(int argc, const char * argv[])
{
	const int success(0);

	// Acquire filename passed as argument
	string filename = "test";
	if (argc == 2) {
		filename = argv[1];
	} else {
		// Error could go here. This is caught during file loading.
		cout << "You must pass a filename argument.\nExample: <application> <filename>\n";
//		exit(1);
	}
	
	// Setup configuration
	app_configuration* config = new app_configuration();
	config->HELP_ON = false;	// default (NO messages)
	config->MAX_TRANSITIONS = 1; // Max number of transitions to perform at a time (default 1)
	config->MAX_ID_CHARS = 32; // Max number of cells to the left and to the right of the tape head to display in instantaneous description. (default: 32 in each direction)
	config->FILENAME_BASE = filename;
	
	cout << setfill('_') << setw(20) << "" << endl;
	cout << "Hello, Turing Machine World!\n";
		
	// Load Turing Machine Object
	Turing_Machine tm(filename);
//	tm.view_definition();
	if (!tm.is_valid_definition()) {
		cout << "Invalid definition: Shutting down.\n";
		return -1;
	}
	
	// Load Menu System
	Menu menu(config, &tm);
	

	// Application Loop
	while (menu.menuLoop()) {
				
	}
	
	
	
    return success;
}



