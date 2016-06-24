#include "node.h"
#include "macros.h"

void
Node::pawn(int x) {
	static int di;
	if (turn == "white") {
		di = up;
	}
	else {
		di = dn;
	}
	if (empty(board.at(x + di))) {
		moves.push_back(add_int_strings(x, x + di));
		if (dub(x) && empty(board.at(x + 2 * di))) {
			moves.push_back(add_int_strings(x, x + 2 * di));
		}
	}
	//cross
	if (foe(board.at(x + di + rt))) {
		moves.push_back(add_int_strings(x, x + di + rt));
	}
	if (foe(board.at(x + di + lt))) {
		moves.push_back(add_int_strings(x, x + di + lt));
	}
	//en passant
	if (x + di + rt == en_passant) {
		moves.push_back(add_int_strings(x, x + di + rt));
	}
	if (x + di + lt == en_passant) {
		moves.push_back(add_int_strings(x, x + di + lt));
	}
}
