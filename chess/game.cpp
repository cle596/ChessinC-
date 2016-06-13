#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "game.h"

#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)

void
Game::init() {
	this->root.turn = "white";
	this->root.en_passant = 0;
	this->root.castle[0] = true;
	this->root.castle[1] = true;
	this->root.castle[2] = true;
	this->root.castle[3] = true;
	this->castle_input[0] = "wk00";
	this->castle_input[1] = "wq00";
	this->castle_input[2] = "bk00"; 
	this->castle_input[3] = "bq00";
	this->root.rotate_pst(this->root.pawn_pst, this->root.npawn_pst);
	this->root.rotate_pst(this->root.knight_pst, this->root.nknight_pst);
	this->root.rotate_pst(this->root.bishop_pst, this->root.nbishop_pst);
	this->root.rotate_pst(this->root.rook_pst, this->root.nrook_pst);
	this->root.rotate_pst(this->root.queen_pst, this->root.nqueen_pst);
	this->root.rotate_pst(this->root.king_pst, this->root.nking_pst);
	std::cout << "time to play chess cocksucka!" << std::endl;
}

void
Game::take_input() {
	std::cout << "make yo move sucka: ";
	while (true) {
		std::cin >> this->input;
		if (this->input.length() == 4) {
			break;
		}
		else {
			std::cout << "not a legal move" << std::endl;
			std::cout << "make yo move sucka: ";
		}
	}
	if (in_array(this->input, castle_input)) {
		this->pos = this->input;
	}
	else {
		this->pos = move_to_pos(this->input);
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
	if (in_array(this->pos, castle_input)) {
		if (this->pos == castle_input[0]) {
			this->root.board.replace(95, 1, ".");
			this->root.board.replace(96, 1, "R");
			this->root.board.replace(97, 1, "K");
			this->root.board.replace(98, 1, ".");
		}
		else if (this->pos == castle_input[1]) {
			this->root.board.replace(91, 1, ".");
			this->root.board.replace(92, 1, ".");
			this->root.board.replace(93, 1, "K");
			this->root.board.replace(94, 1, "R");
			this->root.board.replace(95, 1, ".");
		}
		else if (this->pos == castle_input[1]) {
			this->root.board.replace(25, 1, ".");
			this->root.board.replace(26, 1, "r");
			this->root.board.replace(27, 1, "k");
			this->root.board.replace(28, 1, ".");
		}
		else if (this->pos == castle_input[3]) {
			this->root.board.replace(21, 1, ".");
			this->root.board.replace(22, 1, ".");
			this->root.board.replace(23, 1, "k");
			this->root.board.replace(24, 1, "r");
			this->root.board.replace(25, 1, ".");
		}
	}
	else {
		int from = std::stoi(this->pos.substr(0, 2), nullptr);
		int to = std::stoi(this->pos.substr(2, 2), nullptr);
		if (root.board.at(from) == 'K') {
			this->root.castle[0] = false;
			this->root.castle[1] = false;
		}
		else if (root.board.at(from) == 'R'
			&& from == 98) {
			this->root.castle[0] = false;
		}
		else if (root.board.at(from) == 'R'
			&& from == 91) {
			this->root.castle[1] = false;
		}
		else if (root.board.at(from) == 'k') {
			this->root.castle[2] = false;
			this->root.castle[3] = false;
		}
		else if (root.board.at(from) == 'r'
			&& from == 28) {
			this->root.castle[2] = false;
		}
		else if (root.board.at(from) == 'r'
			&& from == 21) {
			this->root.castle[3] = false;
		}
		else if (root.board.at(from) == 'P' &&
			to == from-20) {
			this->root.en_passant = from-10;
		}
		else if (root.board.at(from) == 'p' &&
			to == from + 20) {
			this->root.en_passant = from + 10;
		}
		this->root.board.replace(
			to,
			1,
			std::string(1, this->root.board.at(from))
		);
		this->root.board.replace(from, 1, ".");
	}
}

void 
Game::process_input() {
	this->moves = this->root.gen_moves();
	if (in_vector(this->pos,this->moves)) {
		this->update_root();
		if (this->root.turn.compare("white") == 0) {
			this->root.turn = "black";
			for (int x = 0; x < 6; ++x) {
				this->root.foe[x] = toupper(this->root.foe[x]);
			}
		}
		else {
			this->root.turn = "white";
			for (int x = 0; x < 6; ++x) {
				this->root.foe[x] = tolower(this->root.foe[x]);
			}
		}
		this->root.moves.clear();
	}
	else {
		std::cout << "not a legal move" << std::endl;
	}
}