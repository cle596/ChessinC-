#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "node.h"
//#include "gendefs.h"

#define add_int_strings(x,y) std::to_string(x).append(std::to_string(y))
#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)

const int Node::pawn_pst[120] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 50, 50, 50, 50, 50, 50, 50, 50,  0,
	0, 10, 10, 20, 30, 30, 20, 10, 10,  0,
	0,  5,  5, 10, 25, 25, 10,  5,  5,  0,
	0,  0,  0,  0, 20, 20,  0,  0,  0,  0,
	0,  5, -5,-10,  0,  0,-10, -5,  5,  0,
	0,  5, 10, 10,-20,-20, 10, 10,  5,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

const int Node::knight_pst[120] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,-50,-40,-30,-30,-30,-30,-40,-50,  0,
	0,-40,-20,  0,  0,  0,  0,-20,-40,  0,
	0,-30,  0, 10, 15, 15, 10,  0,-30,  0,
	0,-30,  5, 15, 20, 20, 15,  5,-30,  0,
	0,-30,  0, 15, 20, 20, 15,  0,-30,  0,
	0,-30,  5, 10, 15, 15, 10,  5,-30,  0,
	0,-40,-20,  0,  5,  5,  0,-20,-40,  0,
	0,-50,-40,-30,-30,-30,-30,-40,-50,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

const int Node::bishop_pst[120] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,-20,-10,-10,-10,-10,-10,-10,-20,  0,
	0,-10,  0,  0,  0,  0,  0,  0,-10,  0,
	0,-10,  0,  5, 10, 10,  5,  0,-10,  0,
	0,-10,  5,  5, 10, 10,  5,  5,-10,  0,
	0,-10,  0, 10, 10, 10, 10,  0,-10,  0,
	0,-10, 10, 10, 10, 10, 10, 10,-10,  0,
	0,-10,  5,  0,  0,  0,  0,  5,-10,  0,
	0,-20,-10,-10,-10,-10,-10,-10,-20,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

const int Node::rook_pst[120] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  5, 10, 10, 10, 10, 10, 10,  5,  0,
	0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
	0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
	0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
	0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
	0, -5,  0,  0,  0,  0,  0,  0, -5,  0,
	0,  0,  0,  0,  5,  5,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

const int Node::queen_pst[120] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,-20,-10,-10, -5, -5,-10,-10,-20,  0,
	0,-10,  0,  0,  0,  0,  0,  0,-10,  0,
	0,-10,  0,  5,  5,  5,  5,  0,-10,  0,
	0, -5,  0,  5,  5,  5,  5,  0, -5,  0,
	0,  0,  0,  5,  5,  5,  5,  0, -5,  0,
	0,-10,  5,  5,  5,  5,  5,  0,-10,  0,
	0,-10,  0,  5,  0,  0,  0,  0,-10,  0,
	0,-20,-10,-10, -5, -5,-10,-10,-20,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

const int Node::king_pst[120] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,-30,-40,-40,-50,-50,-40,-40,-30,  0,
	0,-30,-40,-40,-50,-50,-40,-40,-30,  0,
	0,-30,-40,-40,-50,-50,-40,-40,-30,  0,
	0,-30,-40,-40,-50,-50,-40,-40,-30,  0,
	0,-20,-30,-30,-40,-40,-30,-30,-20,  0,
	0,-10,-20,-20,-20,-20,-20,-20,-10,  0,
	0, 20, 20,  0,  0,  0,  0, 20, 20,  0,
	0, 20, 30, 10,  0,  0, 10, 30, 20,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};


int*
Node::rotate_pst(const int* pst, int* npst) {
	for (size_t x = 0; x < 120; ++x) {
		npst[x] = -pst[10 * (11 - (x / 10)) + (x % 10)];
	}
	return npst;
}

int Node::npawn_pst[120];
int Node::nknight_pst[120];
int Node::nbishop_pst[120];
int Node::nrook_pst[120];
int Node::nqueen_pst[120];
int Node::nking_pst[120];

void 
Node::set_npst() {
	rotate_pst(pawn_pst, npawn_pst);
	rotate_pst(knight_pst, nknight_pst);
	rotate_pst(bishop_pst, nbishop_pst);
	rotate_pst(rook_pst, nrook_pst);
	rotate_pst(queen_pst, nqueen_pst);
	rotate_pst(king_pst, nking_pst);
}


const int Node::Nmoves[] = {
	2 * up + rt,up + 2 * rt,dn + 2 * rt,2 * dn + rt,
	2 * dn + lt,dn + 2 * lt,up + 2 * lt,2 * up + lt
};
const int Node::Bmoves[] = {
	up + rt,dn + rt,
	dn + lt,up + lt
};
const int Node::Rmoves[] = {
	up,rt,
	dn,lt
};
const int Node::Kmoves[] = {
	up,up + rt,rt,dn + rt,dn,
	dn + lt,lt,up + lt
};

void Node::castle_reset() {
	for (size_t x = 0; x < 4; ++x) {
		this->castle[x] = true;
	}
}

void Node::castle_copy(const bool* b,bool* bb) {
	for (size_t x = 0; x < 4; ++x) {
		bb[x] = b[x];
	}
}

const std::string Node::castle_input[4] = { "wk00" ,"wq00","bk00","bq00" };

Node::Node()
{
	this->turn = "white";
	this->en_passant = 0;
	this->castle_reset();
	set_npst();
}

Node::Node(const Node & n)
{
	this->board = n.board;
	this->en_passant = n.en_passant;
	castle_copy(n.castle,this->castle);
	set_npst();
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
			this->foe[x] = tolower(this->foe[x]);
		}
	}
	else {
		for (int x = 0; x < 6; ++x) {
			this->foe[x] = toupper(this->foe[x]);
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

void Node::flip_dub() {
	if (this->turn.compare("white") == 0) {
		for (int x = 0; x < 8; ++x) {
			this->dub[x] = wdub[x];
		}
	}
	else {
		for (int x = 0; x < 8; ++x) {
			this->dub[x] = bdub[x];
		}
	}
}

