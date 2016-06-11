#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "chess.h"

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

std::string pos_to_move(std::string pos) {
	std::string move;
	std::map<int, char> cols;
	std::map<int, char> rows;
	for (int x = 0; x < 8; ++x) {
		cols[1 + x] = 97 + x;
	}
	for (int x = 0; x < 8; ++x) {
		rows[9 - x] = 49 + x;
	}
	int posi1 = std::stoi(pos.substr(0,2),nullptr);
	int posi2 = std::stoi(pos.substr(2, 2), nullptr);
	move += cols.at(posi1 - (posi1 / 10)*10);
	move += rows.at(posi1 / 10);
	move += cols.at(posi2 - (posi2 / 10) * 10);
	move += rows.at(posi2 / 10);
	return move;
}

std::vector<std::string>
translate_moves(std::vector<std::string> moves) {
	std::vector<std::string> translated_moves;
	for (size_t x = 0; x < moves.size(); ++x) {
		translated_moves.push_back(pos_to_move(moves.at(x)));
	}
	return translated_moves;
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
	std::string sub = input.substr(0, 2);
	int pos = std::stoi(sub, nullptr, 10);
	std::vector<std::string> moves = gen_moves(board);
	std::vector<std::string> tmoves = translate_moves(moves);
	std::cout << tmoves.at(0) << std::endl;
	
 	return 0;
}