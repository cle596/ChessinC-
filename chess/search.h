#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "game.h"

class Search {
public:

	std::string bmove;
	std::vector<Node> db;
	std::vector<std::string> history;
	int depth;
	
	int recurse(Node&,int,int,int);
	int guess(Node&,int);
	void tcurse(Node&);
	void sort(std::vector<std::string>& moves, std::string move);
};