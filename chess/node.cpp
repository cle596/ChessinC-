#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "gendefs.h"
#include "node.h"
#include "score.h"

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
	static int di;
	if (this->turn.compare("white")==0) {
		di = up;
	}
	else if (this->turn.compare("black")==0) {
		di = dn;
	}
	if (this->board.at(x + di) == '.') {
		this->moves.push_back(
			add_int_strings(x, x + di)
		);
		if (this->board.at(x + 2 * di) == '.') {
			this->moves.push_back(
				add_int_strings(x, x + 2 * di)
			);
			this->en_passant = x + di;
		}
	}
	//cross
	else if (in_array(this->board.at(x + di + rt),foe)) {
		this->moves.push_back(
			add_int_strings(x, x + di + rt)
		);
	}
	else if (in_array(this->board.at(x + di + lt), foe)) {
		this->moves.push_back(
			add_int_strings(x, x + di + lt)
		);
	}
	//en passant
	else if (x + di + rt == this->en_passant) {
		this->moves.push_back(
			add_int_strings(x, x + di + rt)
		);
	}
	else if (x + di + lt == this->en_passant) {
		this->moves.push_back(
			add_int_strings(x, x + di + lt)
		);
	}
}

void
Node::knight(int x) {
	for (int y = 0; y < 8; ++y) {
		if (this->board.at(x + Nmoves[y]) == '.' ||
			in_array(this->board.at(x + Nmoves[y]), foe)) {
			this->moves.push_back(
				add_int_strings(x, x + Nmoves[y])
			);
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
				this->moves.push_back(
					add_int_strings(x, x + z*Bmoves[y])
				);
			}
			else if (in_array(this->board.at(x + z*Bmoves[y]), foe)) {
				this->moves.push_back(
					add_int_strings(x, x + z*Bmoves[y])
				);
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
				this->moves.push_back(
					add_int_strings(x, x + z*Rmoves[y])
				);
			}
			else if (in_array(this->board.at(x + z*Rmoves[y]), foe)) {
				this->moves.push_back(
					add_int_strings(x, x + z*Rmoves[y])
				);
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
				this->moves.push_back(
					add_int_strings(x, x + z*Kmoves[y])
				);
			}
			else if (in_array(this->board.at(x + z*Kmoves[y]), foe)) {
				this->moves.push_back(
					add_int_strings(x, x + z*Kmoves[y])
				);
				break;
			}
			z += 1;
		}
	}
}

void
Node::king(int x) {
	for (int y = 0; y < 8; ++y) {
		if (this->board.at(x + Kmoves[y]) == '.' ||
			in_array(this->board.at(x + Kmoves[y]), foe)) {
			this->moves.push_back(
				add_int_strings(x, x + Kmoves[y])
			);
		}
	}
	if (this->castle[0] &&
		this->board.at(96) == '.' &&
		this->board.at(97) == '.'){
		this->moves.push_back("wk00");
	}
	if (this->castle[1] &&
		this->board.at(92) == '.' &&
		this->board.at(93) == '.' &&
		this->board.at(94) == '.') {
		this->moves.push_back("wq00");
	}
}

std::vector<std::string>
Node::gen_moves() {
	std::vector<std::string> moves;
	char pawn = 'P';
	char knight = 'N';
	char bishop = 'B';
	char rook = 'R';
	char queen = 'Q';
	char king = 'K';
	if (this->turn.compare("black") == 0) {
		pawn = tolower(pawn);
		knight = tolower(knight);
		bishop = tolower(bishop);
		rook = tolower(rook);
		queen = tolower(queen);
		king = tolower(king);
	}
	for (size_t x = 0; x < this->board.length(); ++x) {
		if (board.at(x)==pawn) {
			this->pawn(x);
		}
		else if (board.at(x)==knight) {
			this->knight(x);
		}
		else if (board.at(x)==bishop) {
			this->bishop(x);
		}
		else if (board.at(x)==rook) {
			this->rook(x);
		}
		else if (board.at(x)==queen) {
			this->queen(x);
		}
		else if (board.at(x)==king) {
			this->king(x);
		}
	}
	return this->moves;
}

int
Node::score() {
	for (size_t x = 0; x < this->board.length(); ++x) {

	}
	return 0;
}