#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "game.h"

#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()

void
Game::init() {
	std::cout << "time to play chess cocksucka!\n";
}

void
Game::take_input() {
	std::cout << "make yo move sucka: ";
	std::cin >> this->input;
	this->pos = move_to_pos(this->input);
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
	int posi1 = std::stoi(pos.substr(0, 2), nullptr);
	int posi2 = std::stoi(pos.substr(2, 2), nullptr);
	move += cols.at(posi1 - (posi1 / 10) * 10);
	move += rows.at(posi1 / 10);
	move += cols.at(posi2 - (posi2 / 10) * 10);
	move += rows.at(posi2 / 10);
	return move;
}

std::vector<std::string>
Game::translate_moves(std::vector<std::string> moves) {
	std::vector<std::string> translated_moves;
	for (size_t x = 0; x < moves.size(); ++x) {
		translated_moves.push_back(
			this->pos_to_move(moves.at(x))
		);
	}
	return translated_moves;
}

void
Game::update_root() {
	int from = std::stoi(this->pos.substr(0, 2), nullptr);
	int to = std::stoi(this->pos.substr(2, 2), nullptr);
	this->root.board.replace(
		to, 
		1, 
		std::string(1, this->root.board.at(from))
	);
	this->root.board.replace(from, 1, ".");
}

void 
Game::process_input() {
	this->moves = this->root.gen_moves();
	if (in_vector(this->pos,this->moves)) {
		this->update_root();
		this->root.print();
	}
	else {
		std::cout << "not a legal move" << std::endl;
	}
}