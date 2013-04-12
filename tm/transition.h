//
//  transition.h
//  tm
//
//  Created by Lansdon Page on 3/25/13.
//  Copyright (c) 2013 Lansdon Page. All rights reserved.
//

#ifndef __tm__transition__
#define __tm__transition__

#include "Direction.h"
#include <string>
using namespace std;

class Transition
{

public:
	Transition(string source_state, char read_character, string destination_state, char write_character, Direction move_direction);
	string source_state() const;
	char read_character() const;
	string destination_state() const;
	char write_character() const;
	Direction move_direction() const;
	
private:
	string source;
	char read;
	string destination;
	char write;
	Direction move;
	
};

#endif /* defined(__tm__transition__) */
