#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "node.h"
#include "macros.h"

int*
Node::rotate_pst(const int* pst,int* npst) {
	for (size_t x = 0; x < 120; ++x) {
		npst[x] = -pst[10 * (11 - (x / 10)) + (x % 10)];
	}
	return npst;
}

void 
Node::set_npst() {
	Node::rotate_pst(Node::pawn_pst, Node::npawn_pst);
	Node::rotate_pst(Node::knight_pst, Node::nknight_pst);
	Node::rotate_pst(Node::bishop_pst, Node::nbishop_pst);
	Node::rotate_pst(Node::rook_pst, Node::nrook_pst);
	Node::rotate_pst(Node::queen_pst, Node::nqueen_pst);
	Node::rotate_pst(Node::king_pst, Node::nking_pst);
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
		castle[x] = true;
	}
}

void Node::castle_copy(const bool* b,bool* bb) {
	for (size_t x = 0; x < 4; ++x) {
		bb[x] = b[x];
	}
}

Node::Node()
{
	turn = "white";
	en_passant = 0;
	castle_reset();
}

Node::Node(const Node & n)
{
	board = n.board;
	en_passant = n.en_passant;
	castle_copy(n.castle,castle);
	flips();
}

void
Node::update_board(std::string pos) {
	if (in_array(pos, castle_input)) {
		if (pos == castle_input[0]) {
			board.replace(95, 4, ".RK.");
		}
		else if (pos == castle_input[1]) {
			board.replace(91, 5, "..KR.");
		}
		else if (pos == castle_input[1]) {
			board.replace(25, 4, ".rk.");
		}
		else if (pos == castle_input[3]) {
			board.replace(21, 5, "..kr.");
		}
	}
	else {
		int from = std::stoi(pos.substr(0, 2));
		int to = std::stoi(pos.substr(2, 2));
		if (board.at(from) == 'K') {
			castle[0] = false;
			castle[1] = false;
		}
		else if (board.at(from) == 'R'
			&& from == 98) {
			castle[0] = false;
		}
		else if (board.at(from) == 'R'
			&& from == 91) {
			castle[1] = false;
		}
		else if (board.at(from) == 'k') {
			castle[2] = false;
			castle[3] = false;
		}
		else if (board.at(from) == 'r'
			&& from == 28) {
			castle[2] = false;
		}
		else if (board.at(from) == 'r'
			&& from == 21) {
			castle[3] = false;
		}
		else if (board.at(from) == 'P' &&
			to == from - 20) {
			en_passant = from - 10;
		}
		else if (board.at(from) == 'p' &&
			to == from + 20) {
			en_passant = from + 10;
		}
		else if (board.at(from) == 'P' &&
			to == en_passant) {
			board.at(en_passant + 10) = '.';
			en_passant = 0;
		}
		else if (board.at(from) == 'p' &&
			to == en_passant) {
			board.at(en_passant - 10) = '.';
			en_passant = 0;
		}
		board.replace(
			to,
			1,
			std::string(1, board.at(from))
		);
		board.replace(from, 1, ".");
	}
	flips();
}

void
Node::print() {
	std::string formatted_board;
	for (size_t x = 0; x < board.length(); ++x) {
		formatted_board += board.at(x);
		if (board.at(x) != '\n') {
			formatted_board += ' ';
		}
	}
	std::cout << formatted_board << std::endl;
}

std::vector<std::string>
Node::gen_moves() {
	char pa = 'P'; char na = 'N';
	char ba = 'B'; char ra = 'R';
	char qa = 'Q'; char ka = 'K';
	if (turn.compare("black") == 0) {
		pa = tolower(pa);
		na = tolower(na);
		ba = tolower(ba);
		ra = tolower(ra);
		qa = tolower(qa);
		ka = tolower(ka);
	}
	for (size_t x = 0; x < board.length(); ++x) {
		if (board.at(x)==pa) {
			pawn(x);
		}
		else if (board.at(x)==na) {
			knight(x);
		}
		else if (board.at(x)==ba) {
			bishop(x);
		}
		else if (board.at(x)==ra) {
			rook(x);
		}
		else if (board.at(x)==qa) {
			queen(x);
		}
		else if (board.at(x)==ka) {
			king(x);
		}
	}
	return moves;
}

int
Node::score() {
	int score = 0;
	for (size_t x = 0; x < board.length(); ++x) {
		if (board.at(x) == 'P') {
			score += P;
			score += pawn_pst[x];
		}
		else if (board.at(x) == 'p') {
			score += -P;
			score += npawn_pst[x];
		}
		else if (board.at(x) == 'N') {
			score += N;
			score += knight_pst[x];
		}
		else if (board.at(x) == 'n') {
			score += -N;
			score += nknight_pst[x];
		}
		else if (board.at(x) == 'B') {
			score += B;
			score += bishop_pst[x];
		}
		else if (board.at(x) == 'b') {
			score += -B;
			score += nbishop_pst[x];
		}
		else if (board.at(x) == 'R') {
			score += R;
			score += rook_pst[x];
		}
		else if (board.at(x) == 'r') {
			score += -R;
			score += nrook_pst[x];
		}
		else if (board.at(x) == 'Q') {
			score += Q;
			score += queen_pst[x];
		}
		else if (board.at(x) == 'q') {
			score += -Q;
			score += nqueen_pst[x];
		}
		else if (board.at(x) == 'K') {
			score += K;
			score += king_pst[x];
		}
		else if (board.at(x) == 'k') {
			score += -K;
			score += nking_pst[x];
		}
	}
	return score;
}

void Node::flip_foe() {
	if (turn.compare("white") == 0) {
		for (int x = 0; x < 6; ++x) {
			foe[x] = tolower(foe[x]);
		}
	}
	else {
		for (int x = 0; x < 6; ++x) {
			foe[x] = toupper(foe[x]);
		}
	}
}

void Node::flip_turn() {
	if (turn.compare("white") == 0) {
		turn = "black";
	}
	else {
		turn = "white";
	}
}

void Node::flip_dub() {
	if (turn.compare("white") == 0) {
		for (int x = 0; x < 8; ++x) {
			dub[x] = wdub[x];
		}
	}
	else {
		for (int x = 0; x < 8; ++x) {
			dub[x] = bdub[x];
		}
	}
}

void
Node::flips() {
	flip_turn();
	flip_foe();
	flip_dub();
}