#include "node.h"
#include "macros.h"

#define incr Kmoves[y]

void
Node::king(int x) {
	for (int y = 0; y < 8; ++y) {
		if (empty_or_foe(board.at(x + incr))) {
			moves.push_back(add_int_strings(x, x + incr));
		}
	}
	if (turn == "white") {
		if (castle[0] &&
			board.substr(96,2) == "..") {
			moves.push_back("wk00");
		}
		if (castle[1] &&
			board.substr(92,3) == "...") {
			moves.push_back("wq00");
		}
	}
	else {
		if (castle[2] &&
			board.substr(26,2) == "..") {
			moves.push_back("bk00");
		}
		if (castle[3] &&
			board.substr(22,3) == "...") {
			moves.push_back("bq00");
		}
	}
}