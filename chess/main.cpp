#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "chess.h"
#include "gen.h"
#include "node.h"

int main() {

	std::string input;
	std::vector<std::string> moves;
	std::vector<std::string> tmoves;

	std::cout << "time to play chess cocksucka!\n";

	Node root = Node();
	root.print();

	while (true) {
		std::cout << "make yo move cocksucka: ";
		std::cin >> input;
		input = move_to_pos(input);
		moves = root.gen_moves();
		if (std::find(moves.begin(), moves.end(), input) != moves.end()) {
			root.board = new_board(root.board, input);
			root.print();
		}
		else {
			std::cout << "not a legal move" << std::endl;
		}
	}

 	return 0;
}