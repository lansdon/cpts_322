//
//  transition.h
//  tm
//
//	Represents a single transition definition
//
// language: c++
// computer: Dell
// OS: Linux
// course: cpts_322
//  Created by  Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__transition__
#define __tm__transition__

#include <string>
#include "Direction.h"
using namespace std;

class Transition
{

public:
	/////////////////////////////////
	//	Constructor – Creates a transition object initialized with the passed values.
	/////////////////////////////////
	Transition(string source_state, char read_character, string destination_state, char write_character, Direction move_direction);
	
	/////////////////////////////////
	//	Returns the source state
	/////////////////////////////////
	string source_state() const;
	
	/////////////////////////////////
	//	returns the read character
	/////////////////////////////////
	char read_character() const;
	
	/////////////////////////////////
	//	returns the destination state
	/////////////////////////////////
	string destination_state() const;
	
	/////////////////////////////////
	//	returns the write character
	/////////////////////////////////
	char write_character() const;
	
	/////////////////////////////////
	//	returns the move direction
	/////////////////////////////////
	Direction move_direction() const;
	
private:
	string source; //	The starting (source) state of the transition
	char read;		//	The character that is read by the tape head
	string destination;  //	The destination state after performing the transition
	char write;		//	The character to be written to the current cell when performing the transition
	Direction move;	//	The direction to move the tape head when performing the transition
	
};

#endif /* defined(__tm__transition__) */
