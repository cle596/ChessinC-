#pragma once

#include <string>
#include <vector>
#include <string>

#include "node.h"

class Game {

public:

	//node maintained for the game
	Node root = Node();

	//input strings
	std::string input;
	std::string pos;

	//for debugging purposes
	std::vector<std::string> moves;
	std::vector<std::string> tmoves;

	void init(); // start msg

	void take_input(std::string); //check string length of input and if its a castle move

	//convert between number index and alphabetic move string
	std::string move_to_pos(std::string move);
	std::string pos_to_move(std::string pos);

	//translate alphabetic move to index position string
	std::vector<std::string> translate_moves(std::vector<std::string>);

	//check if input move is legal by generating possible move vector 
	//and update the game's node 
	void process_input(); 

};

