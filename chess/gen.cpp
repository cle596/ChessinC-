#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "gen.h"

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
gen_moves(std::string board) {
	std::vector<std::string> moves;
	for (size_t x = 0; x < board.length(); ++x) {
		if (board.at(x) == 'P') {
			moves = pawn(moves,board,x);
		}
		else if (board.at(x) == 'N') {
			for (int y = 0; y < 8; ++y) {
				if (board.at(x + Nmoves[y]) == '.' ||
					std::find(std::begin(foe), std::end(foe), board.at(x + Nmoves[y])) != std::end(foe)) {
					moves.push_back(std::to_string(x).append(std::to_string(x + Nmoves[y])));
				}
			}
		}
		else if (board.at(x) == 'B') {
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
		}
		else if (board.at(x) == 'R') {
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
		}
		else if (board.at(x) == 'Q') {
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
		}
		else if (board.at(x) == 'K') {

		}
	}
	return moves;
}