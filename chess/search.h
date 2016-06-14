#pragma once

#include <iostream>

#include "node.h"
#include "game.h"

class Search {
public:
	int max, min;
	std::string bmove;
	
	void recurse(Node* n);
};