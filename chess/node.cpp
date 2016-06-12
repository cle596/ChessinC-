#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "gendefs.h"
#include "node.h"

void 
Node::print() {
	std::string formatted_board;
	for (size_t x = 0; x < this->board.length(); ++x) {
		formatted_board += this->board.at(x);
		if (this->board.at(x) != '\n') {
			formatted_board += ' ';
		}
	}
	std::cout << formatted_board << std::endl;
}

void
Node::pawn(int x) {
	if (this->board.at(x + up) == '.') {
		this->moves.push_back(add_int_strings(x, x + up));
		if (this->board.at(x + 2 * up) == '.') {
			this->moves.push_back(add_int_strings(x, x + 2 * up));
		}
	}
}

void
Node::knight(int x) {
	for (int y = 0; y < 8; ++y) {
		if (this->board.at(x + Nmoves[y]) == '.' ||
			in_array(this->board.at(x + Nmoves[y]), foe)) {
			this->moves.push_back(add_int_strings(x, x + Nmoves[y]));
		}
	}
}

void
Node::bishop(int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (this->board.at(x + z*Bmoves[y]) == '.' ||
			in_array(this->board.at(x + z*Bmoves[y]), foe)) {
			if (this->board.at(x + z*Bmoves[y]) == '.') {
				this->moves.push_back(add_int_strings(x, x + z*Bmoves[y]));
			}
			else if (in_array(this->board.at(x + z*Bmoves[y]), foe)) {
				this->moves.push_back(add_int_strings(x, x + z*Bmoves[y]));
				break;
			}
			z += 1;
		}
	}
}

void
Node::rook(int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (this->board.at(x + z*Rmoves[y]) == '.' ||
			in_array(this->board.at(x + z*Rmoves[y]), foe)) {
			if (this->board.at(x + z*Rmoves[y]) == '.') {
				this->moves.push_back(add_int_strings(x, x + z*Rmoves[y]));
			}
			else if (in_array(this->board.at(x + z*Rmoves[y]), foe)) {
				this->moves.push_back(add_int_strings(x, x + z*Rmoves[y]));
				break;
			}
			z += 1;
		}
	}
}

void
Node::queen(int x) {
	for (int y = 0; y < 8; ++y) {
		int z = 1;
		while (this->board.at(x + z*Kmoves[y]) == '.' ||
			in_array(this->board.at(x + z*Kmoves[y]), foe)) {
			if (this->board.at(x + z*Kmoves[y]) == '.') {
				this->moves.push_back(add_int_strings(x, x + z*Kmoves[y]));
			}
			else if (in_array(this->board.at(x + z*Kmoves[y]), foe)) {
				this->moves.push_back(add_int_strings(x, x + z*Kmoves[y]));
				break;
			}
			z += 1;
		}
	}
}

void
Node::king(int x) {
	for (int y = 0; y < 8; ++y) {
		if (this->board.at(x + Kmoves[y]) == '.') {
			this->moves.push_back(add_int_strings(x, x + Kmoves[y]));
		}
		else if (in_array(this->board.at(x + Kmoves[y]), foe)) {
			this->moves.push_back(add_int_strings(x, x + Kmoves[y]));
			break;
		}
	}
}

std::vector<std::string>
Node::gen_moves() {
	std::vector<std::string> moves;
	for (size_t x = 0; x < this->board.length(); ++x) {
		if (this->board.at(x) == 'P') {
			this->pawn(x);
		}
		else if (board.at(x) == 'N') {
			this->knight(x);
		}
		else if (board.at(x) == 'B') {
			this->bishop(x);
		}
		else if (board.at(x) == 'R') {
			this->rook(x);
		}
		else if (board.at(x) == 'Q') {
			this->queen(x);
		}
		else if (board.at(x) == 'K') {
			this->king(x);
		}
	}
	return this->moves;
}