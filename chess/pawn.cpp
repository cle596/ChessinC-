#include "node.h"
#include "macros.h"

void
Node::pawn(int x) {
	static int di;
	if (turn.compare("white") == 0) {
		di = up;
	}
	else if (turn.compare("black") == 0) {
		di = dn;
	}
	if (board.at(x + di) == '.') {
		moves.push_back(
			add_int_strings(x, x + di)
		);
		if (in_array(x, dub) &&
			board.at(x + 2 * di) == '.') {
			moves.push_back(
				add_int_strings(x, x + 2 * di)
			);
		}
	}
	//cross
	if (in_array(board.at(x + di + rt), foe)) {
		moves.push_back(
			add_int_strings(x, x + di + rt)
		);
	}
	if (in_array(board.at(x + di + lt), foe)) {
		moves.push_back(
			add_int_strings(x, x + di + lt)
		);
	}
	//en passant
	if (x + di + rt == en_passant) {
		moves.push_back(
			add_int_strings(x, x + di + rt)
		);
	}
	if (x + di + lt == en_passant) {
		moves.push_back(
			add_int_strings(x, x + di + lt)
		);
	}
}
