#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "game.h"

class Search {
public:

	std::string bmove;
	std::vector<Node> cands;
	int depth;
	
	int recurse(Node&,int,int,int);
	void tcurse(Node&);

};