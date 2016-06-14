#pragma once

#include <iostream>

#include "node.h"
#include "game.h"

class Search {
public:
	Game* g;
	int max, min;
	std::string bmove;
	Search(Game* g) {
		this->g = g;
	}
	
	void recurse();
};