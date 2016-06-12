#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "chess.h"

int main() {
	std::string myboard = init_board;
	std::string input;
	std::vector<std::string> moves;
	std::vector<std::string> tmoves;
	std::cout << "time to play chess cocksucka!\n";
	std::cout << add_space_to_board(myboard) << std::endl;
	while (true) {
		std::cout << "make yo move cocksucka: ";
		std::cin >> input;
		input = move_to_pos(input);
		moves = gen_moves(myboard);
		tmoves = translate_moves(moves);
		if (std::find(moves.begin(), moves.end(), input) != moves.end()) {
			myboard = new_board(myboard, input);
			std::cout << add_space_to_board(myboard) << std::endl;
		}
		else {
			std::cout << "not a legal move" << std::endl;
		}
	}
 	return 0;
}