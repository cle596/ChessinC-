#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

std::vector<std::string>
gen_moves(std::string board) {
	std::vector<std::string> moves;
	int up = -10;
	int dn = 10;
	int lt = -1;
	int rt = 1;
	char ally[] = { 'P','N','B','R','Q','K' };
	char foe[] = { 'p','n','b','r','q','k' };
	int Nmoves[] = {
		2 * up + rt,up + 2 * rt,dn + 2 * rt,2 * dn + rt,
		2 * dn + lt,dn + 2 * lt,up + 2 * lt,2 * up + lt
	};
	int Bmoves[] = {
		up + rt,dn + rt,
		dn + lt,up + lt
	};
	int Rmoves[] = {
		up,rt,
		dn,lt
	};
	int Kmoves[] = {
		up,up + rt,rt,dn + rt,dn,
		dn + lt,lt,up + lt
	};
	for (size_t x = 0; x < board.length(); ++x) {
		if (board.at(x) == 'P') {
			if (board.at(x + up) == '.') {
				moves.push_back(std::to_string(x).append(std::to_string(x + up)));
				if (board.at(x + 2 * up) == '.') {
					moves.push_back(std::to_string(x).append(std::to_string(x + 2 * up)));
				}
			}
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
				while (board.at(x + z*Kmoves[y]) == '.' ||
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