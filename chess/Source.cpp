﻿#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::string add_space_to_board(std::string board) {
	std::string formatted_board;
	for (size_t x = 0; x < board.length(); ++x) {
		formatted_board += board.at(x);
		if (board.at(x) != '\n') {
			formatted_board.append(" ");
		}
	}
	return formatted_board;
}

std::string move_to_pos(std::string move) {
	std::string pos;
	std::map<char, int> cols;
	std::map<char, int> rows;
	for (int x = 0; x < 8; ++x) {
		cols[97+x] = 2+x;
	}
	for (int x = 0; x < 8; ++x) {
		rows[49 + x] = 90 - 10*x;
	}
	for (int x = 0; x < 3; x+=2) {
		pos.append(std::to_string(cols[move.at(x)]+ rows[move.at(x + 1)]));
	}
	return pos;
}

std::string pos_to_move(int from, int to) {
	std::string move;
	return move;
}

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
		2*up+rt,up+2*rt,dn+2*rt,2*dn+rt,
		2*dn+lt,dn+2*lt,up+2*lt,2*up+lt
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
					moves.push_back(std::to_string(x).append(std::to_string(x + 2*up)));
				}
			}
		}
		else if (board.at(x) == 'N') {
			for (int y = 0; y < 8; ++y) {
				if (board.at(x+Nmoves[y]) == '.' ||
					std::find(std::begin(foe), std::end(foe), board.at(x + Nmoves[y])) != std::end(foe)) {
					moves.push_back(std::to_string(x).append(std::to_string(x + Nmoves[y])));
				}
			}
		}
		else if (board.at(x) == 'B') {
			for (int y = 0; y < 8; ++y) {
				int z = 1;
				while (board.at(x + z*Kmoves[y])=='.' ||
					std::find(std::begin(foe),std::end(foe),board.at(x+z*Kmoves[y]))!=std::end(foe)) {
					if (board.at(x + z*Kmoves[y]) == '.') {
						moves.push_back(std::to_string(x).append(std::to_string(x+z*Kmoves[y])));
					}
					else if (std::find(std::begin(foe),std::end(foe),board.at(x+z*Kmoves[y]))!=std::end(foe)) {
						moves.push_back(std::to_string(x).append(std::to_string(x + z*Kmoves[y])));
						break;
					}
					z += 1;
				}
			}
		}
		else if (board.at(x) == 'R') {

		}
		else if (board.at(x) == 'Q') {

		}
		else if (board.at(x) == 'K') {

		}
	}
	return moves;
}

int main() {
	std::cout << "time to play chess cocksucka!\n";
	std::string input;
	std::string board =
		"         \n"
		"         \n"
		" rnbqkbnr\n"
		" pppppppp\n"
		" ........\n"
		" ........\n"
		" ........\n"
		" ........\n"
		" PPPPPPPP\n"
		" RNBQKBNR\n"
		"         \n"
		"         \n";
	std::cout << add_space_to_board(board) << std::endl;
	std::cout << "make yo move cocksucka: ";
	std::cin >> input;
	input = move_to_pos(input);
	std::cout << input << std::endl;
	std::string sub = input.substr(0, 2);
	int pos = std::stoi(sub, nullptr, 10);
	std::vector<std::string> moves = gen_moves(board);
	for (size_t x = 0; x < moves.size(); ++x) {
		std::cout << moves.at(x) << std::endl;
	}
	
 	return 0;
}