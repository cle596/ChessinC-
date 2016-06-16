#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "game.h"
#include "macros.h"

void
Game::init() {
	std::cout << "time\nto play\nchess!" << std::endl;
	Node::set_npst();
}

void
Game::process_input() {
	moves = root.gen_moves();
	if (in_vector(pos, moves)) {
		root.update_board(pos);
		root.flips();
		root.moves.clear();
	}
	else {
		std::cout << "not a legal move" << std::endl;
	}
}

void
Game::take_input(std::string move) {
	std::cout << "make yo move sucka: ";
	while (true) {
		if (move.compare("") == 0) {
			std::cin >> input;
		}
		else {
			input = move;
		}
		if (input.length() == 4) {
			break;
		}
		else {
			std::cout << "not a legal move" << std::endl;
			std::cout << "make yo move sucka: ";
		}
	}
	if (in_array(input, Node::castle_input)) {
		pos = input;
	}
	else {
		pos = move_to_pos(input);
	}
}

std::string
Game::move_to_pos(std::string move) {
	std::string pos;
	std::map<char, int> cols;
	std::map<char, int> rows;
	for (int x = 0; x < 8; ++x) {
		cols[97 + x] = 1 + x;
	}
	for (int x = 0; x < 8; ++x) {
		rows[49 + x] = 90 - 10 * x;
	}
	for (int x = 0; x < 3; x += 2) {
		pos.append(
			std::to_string(
				cols[move.at(x)] + 
				rows[move.at(x + 1)]
			)
		);
	}
	return pos;
}

std::string
Game::pos_to_move(std::string pos) {
	std::string move;
	std::map<int, char> cols;
	std::map<int, char> rows;
	for (int x = 0; x < 8; ++x) {
		cols[1 + x] = 97 + x;
	}
	for (int x = 0; x < 8; ++x) {
		rows[9 - x] = 49 + x;
	}
	int p1 = std::stoi(pos.substr(0, 2), nullptr);
	int p2 = std::stoi(pos.substr(2, 2), nullptr);
	move += cols.at(p1 - (p1 / 10) * 10);
	move += rows.at(p1 / 10);
	move += cols.at(p2 - (p2 / 10) * 10);
	move += rows.at(p2 / 10);
	return move;
}

std::vector<std::string>
Game::translate_moves(std::vector<std::string> moves) {
	for (size_t x = 0; x < moves.size(); ++x) {
		tmoves.push_back(
			pos_to_move(moves.at(x))
		);
	}
	return tmoves;
}

