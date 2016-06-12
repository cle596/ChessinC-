#pragma once

#include <string>
#include <vector>
#include <string>

#include "node.h"

class Game {

public:

	std::string input;
	std::string pos;
	std::vector<std::string> moves;
	std::vector<std::string> tmoves;
	std::string castle_input[4];

	Node root = Node();

	void init();
	void take_input();
	std::string move_to_pos(std::string move);
	std::string pos_to_move(std::string pos);
	std::vector<std::string> translate_moves(std::vector<std::string>);
	void update_root();
	void process_input();

};

