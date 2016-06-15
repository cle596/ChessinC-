#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "gendefs.h"
#include "node.h"

#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)

Node::Node()
{
	this->turn = "white";
	this->en_passant = 0;
	this->castle[0] = true;
	this->castle[1] = true;
	this->castle[2] = true;
	this->castle[3] = true;
	this->castle_input[0] = "wk00";
	this->castle_input[1] = "wq00";
	this->castle_input[2] = "bk00";
	this->castle_input[3] = "bq00";
	this->rotate_pst(this->pawn_pst, this->npawn_pst);
	this->rotate_pst(this->knight_pst, this->nknight_pst);
	this->rotate_pst(this->bishop_pst, this->nbishop_pst);
	this->rotate_pst(this->rook_pst, this->nrook_pst);
	this->rotate_pst(this->queen_pst, this->nqueen_pst);
	this->rotate_pst(this->king_pst, this->nking_pst);
}

Node::Node(const Node & n)
{
	this->board = n.board;
	/*
	if (n.turn.compare("white") == 0) {
		this->turn = "black";
	}
	else {
		this->turn = "white";
	}
	*/
	this->en_passant = n.en_passant;
	this->castle[0] = n.castle[0];
	this->castle[1] = n.castle[1];
	this->castle[2] = n.castle[2];
	this->castle[3] = n.castle[3];
	this->castle_input[0] = "wk00";
	this->castle_input[1] = "wq00";
	this->castle_input[2] = "bk00";
	this->castle_input[3] = "bq00";
	this->rotate_pst(this->pawn_pst, this->npawn_pst);
	this->rotate_pst(this->knight_pst, this->nknight_pst);
	this->rotate_pst(this->bishop_pst, this->nbishop_pst);
	this->rotate_pst(this->rook_pst, this->nrook_pst);
	this->rotate_pst(this->queen_pst, this->nqueen_pst);
	this->rotate_pst(this->king_pst, this->nking_pst);
}

void
Node::update_board(std::string pos) {
	if (in_array(pos, castle_input)) {
		if (pos == this->castle_input[0]) {
			this->board.replace(95, 1, ".");
			this->board.replace(96, 1, "R");
			this->board.replace(97, 1, "K");
			this->board.replace(98, 1, ".");
		}
		else if (pos == this->castle_input[1]) {
			this->board.replace(91, 1, ".");
			this->board.replace(92, 1, ".");
			this->board.replace(93, 1, "K");
			this->board.replace(94, 1, "R");
			this->board.replace(95, 1, ".");
		}
		else if (pos == this->castle_input[1]) {
			this->board.replace(25, 1, ".");
			this->board.replace(26, 1, "r");
			this->board.replace(27, 1, "k");
			this->board.replace(28, 1, ".");
		}
		else if (pos == this->castle_input[3]) {
			this->board.replace(21, 1, ".");
			this->board.replace(22, 1, ".");
			this->board.replace(23, 1, "k");
			this->board.replace(24, 1, "r");
			this->board.replace(25, 1, ".");
		}
	}
	else {
		int from = std::stoi(pos.substr(0, 2), nullptr);
		int to = std::stoi(pos.substr(2, 2), nullptr);
		if (this->board.at(from) == 'K') {
			this->castle[0] = false;
			this->castle[1] = false;
		}
		else if (this->board.at(from) == 'R'
			&& from == 98) {
			this->castle[0] = false;
		}
		else if (this->board.at(from) == 'R'
			&& from == 91) {
			this->castle[1] = false;
		}
		else if (this->board.at(from) == 'k') {
			this->castle[2] = false;
			this->castle[3] = false;
		}
		else if (this->board.at(from) == 'r'
			&& from == 28) {
			this->castle[2] = false;
		}
		else if (this->board.at(from) == 'r'
			&& from == 21) {
			this->castle[3] = false;
		}
		else if (this->board.at(from) == 'P' &&
			to == from - 20) {
			this->en_passant = from - 10;
		}
		else if (this->board.at(from) == 'p' &&
			to == from + 20) {
			this->en_passant = from + 10;
		}
		else if (this->board.at(from) == 'P' &&
			to == this->en_passant) {
			this->board.at(this->en_passant + 10) = '.';
			this->en_passant = 0;
		}
		else if (this->board.at(from) == 'p' &&
			to == this->en_passant) {
			this->board.at(this->en_passant - 10) = '.';
			this->en_passant = 0;
		}
		this->board.replace(
			to,
			1,
			std::string(1, this->board.at(from))
		);
		this->board.replace(from, 1, ".");
	}
}

int*
Node::rotate_pst(const int* pst,int* npst) {
	for (size_t x = 0; x < 120; ++x) {
		npst[x] = -pst[10*(11-(x/10))+(x%10)];
	}
	return npst;
}

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
		}
	}
	//cross
	if (in_array(this->board.at(x + di + rt),this->foe)) {
		this->moves.push_back(
			add_int_strings(x, x + di + rt)
		);
	}
	if (in_array(this->board.at(x + di + lt), this->foe)) {
		this->moves.push_back(
			add_int_strings(x, x + di + lt)
		);
	}
	//en passant
	if (x + di + rt == this->en_passant) {
		this->moves.push_back(
			add_int_strings(x, x + di + rt)
		);
	}
	if (x + di + lt == this->en_passant) {
		this->moves.push_back(
			add_int_strings(x, x + di + lt)
		);
	}
}

void
Node::knight(int x) {
	for (int y = 0; y < 8; ++y) {
		if (this->board.at(x + Nmoves[y]) == '.' ||
			in_array(this->board.at(x + Nmoves[y]), this->foe)) {
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
			in_array(this->board.at(x + z*Bmoves[y]), this->foe)) {
			if (this->board.at(x + z*Bmoves[y]) == '.') {
				this->moves.push_back(
					add_int_strings(x, x + z*Bmoves[y])
				);
			}
			else if (in_array(this->board.at(x + z*Bmoves[y]), this->foe)) {
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
			in_array(this->board.at(x + z*Rmoves[y]), this->foe)) {
			if (this->board.at(x + z*Rmoves[y]) == '.') {
				this->moves.push_back(
					add_int_strings(x, x + z*Rmoves[y])
				);
			}
			else if (in_array(this->board.at(x + z*Rmoves[y]), this->foe)) {
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
			in_array(this->board.at(x + z*Kmoves[y]), this->foe)) {
			if (this->board.at(x + z*Kmoves[y]) == '.') {
				this->moves.push_back(
					add_int_strings(x, x + z*Kmoves[y])
				);
			}
			else if (in_array(this->board.at(x + z*Kmoves[y]), this->foe)) {
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
			in_array(this->board.at(x + Kmoves[y]), this->foe)) {
			this->moves.push_back(
				add_int_strings(x, x + Kmoves[y])
			);
		}
	}
	if (this->turn.compare("white") == 0) {
		if (this->castle[0] &&
			this->board.at(96) == '.' &&
			this->board.at(97) == '.') {
			this->moves.push_back("wk00");
		}
		if (this->castle[1] &&
			this->board.at(92) == '.' &&
			this->board.at(93) == '.' &&
			this->board.at(94) == '.') {
			this->moves.push_back("wq00");
		}
	}
	else if (this->turn.compare("black")==0){
		if (this->castle[2] &&
			this->board.at(26) == '.' &&
			this->board.at(27) == '.') {
			this->moves.push_back("bk00");
		}
		if (this->castle[3] &&
			this->board.at(22) == '.' &&
			this->board.at(23) == '.' &&
			this->board.at(24) == '.') {
			this->moves.push_back("bq00");
		}
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
	int score = 0;
	for (size_t x = 0; x < this->board.length(); ++x) {
		if (board.at(x) == 'P') {
			score += this->P;
			score += this->pawn_pst[x];
		}
		else if (board.at(x) == 'p') {
			score += -this->P;
			score += this->npawn_pst[x];
		}
		else if (board.at(x) == 'N') {
			score += this->N;
			score += this->knight_pst[x];
		}
		else if (board.at(x) == 'n') {
			score += -this->N;
			score += this->nknight_pst[x];
		}
		else if (board.at(x) == 'B') {
			score += this->B;
			score += this->bishop_pst[x];
		}
		else if (board.at(x) == 'b') {
			score += -this->B;
			score += this->nbishop_pst[x];
		}
		else if (board.at(x) == 'R') {
			score += this->R;
			score += this->rook_pst[x];
		}
		else if (board.at(x) == 'r') {
			score += -this->R;
			score += this->nrook_pst[x];
		}
		else if (board.at(x) == 'Q') {
			score += this->Q;
			score += this->queen_pst[x];
		}
		else if (board.at(x) == 'q') {
			score += -this->Q;
			score += this->nqueen_pst[x];
		}
		else if (board.at(x) == 'K') {
			score += this->K;
			score += this->king_pst[x];
		}
		else if (board.at(x) == 'k') {
			score += -this->K;
			score += this->nking_pst[x];
		}
	}
	return score;
}

void Node::flip_foe() {
	if (this->turn.compare("white") == 0) {
		for (int x = 0; x < 6; ++x) {
			this->foe[x] = toupper(this->foe[x]);
		}
	}
	else {
		for (int x = 0; x < 6; ++x) {
			this->foe[x] = tolower(this->foe[x]);
		}
	}
}

void Node::flip_turn() {
	if (this->turn.compare("white") == 0) {
		this->turn = "black";
	}
	else {
		this->turn = "white";
	}
}