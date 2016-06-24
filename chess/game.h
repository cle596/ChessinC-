#pragma once

#include <string>
#include <vector>
#include <string>

#include "node.h"

using namespace std;

class Game {

public:

	//node maintained for the game
	Node root = Node();

	//input strings
	string input;
	string pos;

	//for debugging purposes
	vector<string> moves;
	vector<string> tmoves;

	void init(); // start msg

	void take_input(string); //check string length of input and if its a castle move

	//convert between number index and alphabetic move string
	string move_to_pos(string move);
	static string pos_to_move(string pos);

	//translate alphabetic move to index position string
	vector<string> translate_moves(vector<string>);

	//check if input move is legal by generating possible move vector 
	//and update the game's node 
	bool process_input(); 

};

