#pragma once

#include <iostream>

#include "node.h"
#include "game.h"

class Search {
public:

	std::string bmove;
	
	int recurse(Node&,int,int,int);
	void tcurse(Node&, int);

};