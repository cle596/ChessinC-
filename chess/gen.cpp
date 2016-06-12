#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "gendefs.h"

void
pawn(std::vector<std::string>& moves,std::string board,int x) {
	if (board.at(x + up) == '.') {
		moves.push_back(add_int_strings(x,x+up));
		if (board.at(x + 2 * up) == '.') {
			moves.push_back(add_int_strings(x,x + 2 * up));
		}
	}
}

void
knight(std::vector<std::string>& moves, std::string board, int x) {
	for (int y = 0; y < 8; ++y) {
		if (board.at(x + Nmoves[y]) == '.' ||
			in_array(board.at(x + Nmoves[y]),foe)) {
			moves.push_back(add_int_strings(x,x + Nmoves[y]));
		}
	}
}

void
bishop(std::vector<std::string>& moves, std::string board, int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (board.at(x + z*Bmoves[y]) == '.' ||
			in_array(board.at(x + z*Bmoves[y]),foe)) {
			if (board.at(x + z*Kmoves[y]) == '.') {
				moves.push_back(add_int_strings(x,x + z*Bmoves[y]));
			}
			else if (in_array(board.at(x + z*Bmoves[y]),foe)) {
				moves.push_back(add_int_strings(x,x + z*Bmoves[y]));
				break;
			}
			z += 1;
		}
	}
}

void
rook(std::vector<std::string>& moves, std::string board, int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (board.at(x + z*Rmoves[y]) == '.' ||
			in_array(board.at(x + z*Rmoves[y]),foe)) {
			if (board.at(x + z*Rmoves[y]) == '.') {
				moves.push_back(add_int_strings(x,x + z*Rmoves[y]));
			}
			else if (in_array(board.at(x + z*Rmoves[y]),foe)) {
				moves.push_back(add_int_strings(x,x + z*Rmoves[y]));
				break;
			}
			z += 1;
		}
	}
}

void
queen(std::vector<std::string>& moves, std::string board, int x) {
	for (int y = 0; y < 8; ++y) {
		int z = 1;
		while (board.at(x + z*Kmoves[y]) == '.' ||
			in_array(board.at(x + z*Kmoves[y]),foe)) {
			if (board.at(x + z*Kmoves[y]) == '.') {
				moves.push_back(add_int_strings(x,x + z*Kmoves[y]));
			}
			else if (in_array(board.at(x + z*Kmoves[y]),foe)) {
				moves.push_back(add_int_strings(x,x + z*Kmoves[y]));
				break;
			}
			z += 1;
		}
	}
}

void
king(std::vector<std::string>& moves, std::string board, int x) {
	for (int y = 0; y < 8; ++y) {
		if (board.at(x + Kmoves[y]) == '.') {
			moves.push_back(add_int_strings(x,x + Kmoves[y]));
		}
		else if (in_array(board.at(x + Kmoves[y]),foe)) {
			moves.push_back(add_int_strings(x,x + Kmoves[y]));
			break;
		}
	}
}

std::vector<std::string>
gen_moves(std::string board) {
	std::vector<std::string> moves;
	for (size_t x = 0; x < board.length(); ++x) {
		if (board.at(x) == 'P') {
			pawn(moves,board,x);
		}
		else if (board.at(x) == 'N') {
			knight(moves, board, x);
		}
		else if (board.at(x) == 'B') {
			bishop(moves, board, x);
		}
		else if (board.at(x) == 'R') {
			rook(moves, board, x);
		}
		else if (board.at(x) == 'Q') {
			queen(moves, board, x);
		}
		else if (board.at(x) == 'K') {
			king(moves, board, x);
		}
	}
	return moves;
}