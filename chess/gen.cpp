#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "gendefs.h"

std::vector<std::string>
pawn(std::vector<std::string> moves,std::string board,int x) {
	if (board.at(x + up) == '.') {
		moves.push_back(std::to_string(x).append(std::to_string(x + up)));
		if (board.at(x + 2 * up) == '.') {
			moves.push_back(std::to_string(x).append(std::to_string(x + 2 * up)));
		}
	}
	return moves;
}

std::vector<std::string>
knight(std::vector<std::string> moves, std::string board, int x) {
	for (int y = 0; y < 8; ++y) {
		if (board.at(x + Nmoves[y]) == '.' ||
			std::find(std::begin(foe), std::end(foe), board.at(x + Nmoves[y])) != std::end(foe)) {
			moves.push_back(std::to_string(x).append(std::to_string(x + Nmoves[y])));
		}
	}
	return moves;
}

std::vector<std::string>
bishop(std::vector<std::string> moves, std::string board, int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (board.at(x + z*Bmoves[y]) == '.' ||
			std::find(std::begin(foe), std::end(foe), board.at(x + z*Bmoves[y])) != std::end(foe)) {
			if (board.at(x + z*Kmoves[y]) == '.') {
				moves.push_back(std::to_string(x).append(std::to_string(x + z*Bmoves[y])));
			}
			else if (std::find(std::begin(foe), std::end(foe), board.at(x + z*Bmoves[y])) != std::end(foe)) {
				moves.push_back(std::to_string(x).append(std::to_string(x + z*Bmoves[y])));
				break;
			}
			z += 1;
		}
	}
	return moves;
}

std::vector<std::string>
rook(std::vector<std::string> moves, std::string board, int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (board.at(x + z*Rmoves[y]) == '.' ||
			std::find(std::begin(foe), std::end(foe), board.at(x + z*Rmoves[y])) != std::end(foe)) {
			if (board.at(x + z*Rmoves[y]) == '.') {
				moves.push_back(std::to_string(x).append(std::to_string(x + z*Rmoves[y])));
			}
			else if (std::find(std::begin(foe), std::end(foe), board.at(x + z*Rmoves[y])) != std::end(foe)) {
				moves.push_back(std::to_string(x).append(std::to_string(x + z*Rmoves[y])));
				break;
			}
			z += 1;
		}
	}
	return moves;
}

std::vector<std::string>
queen(std::vector<std::string> moves, std::string board, int x) {
	for (int y = 0; y < 8; ++y) {
		int z = 1;
		while (board.at(x + z*Kmoves[y]) == '.' ||
			std::find(std::begin(foe), std::end(foe), board.at(x + z*Kmoves[y])) != std::end(foe)) {
			if (board.at(x + z*Kmoves[y]) == '.') {
				moves.push_back(std::to_string(x).append(std::to_string(x + z*Kmoves[y])));
			}
			else if (std::find(std::begin(foe), std::end(foe), board.at(x + z*Kmoves[y])) != std::end(foe)) {
				moves.push_back(std::to_string(x).append(std::to_string(x + z*Kmoves[y])));
				break;
			}
			z += 1;
		}
	}
	return moves;
}

std::vector<std::string>
gen_moves(std::string board) {
	std::vector<std::string> moves;
	for (size_t x = 0; x < board.length(); ++x) {
		if (board.at(x) == 'P') {
			moves = pawn(moves,board,x);
		}
		else if (board.at(x) == 'N') {
			moves = knight(moves, board, x);
		}
		else if (board.at(x) == 'B') {
			moves = bishop(moves, board, x);
		}
		else if (board.at(x) == 'R') {
			moves = rook(moves, board, x);
		}
		else if (board.at(x) == 'Q') {
			moves = queen(moves, board, x);
		}
		else if (board.at(x) == 'K') {

		}
	}
	return moves;
}