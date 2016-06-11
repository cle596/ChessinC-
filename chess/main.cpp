#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "chess.h"

int main() {
	std::cout << "time to play chess cocksucka!\n";
	std::string input;
	std::cout << add_space_to_board(init_board) << std::endl;
	std::cout << "make yo move cocksucka: ";
	std::cin >> input;
	input = move_to_pos(input);
	std::string sub = input.substr(0, 2);
	int pos = std::stoi(sub, nullptr, 10);
	std::vector<std::string> moves = gen_moves(init_board);
	std::vector<std::string> tmoves = translate_moves(moves);
	std::cout << tmoves.at(0) << std::endl;
	
 	return 0;
}