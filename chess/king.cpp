#include "node.h"
#include "macros.h"

void
Node::king(int x) {
	for (int y = 0; y < 8; ++y) {
		if (board.at(x + Kmoves[y]) == '.' ||
			in_array(board.at(x + Kmoves[y]), foe)) {
			moves.push_back(
				add_int_strings(x, x + Kmoves[y])
			);
		}
	}
	if (turn.compare("white") == 0) {
		if (castle[0] &&
			board.substr(96,2) == "..") {
			moves.push_back("wk00");
		}
		if (castle[1] &&
			board.substr(92,3) == "...") {
			moves.push_back("wq00");
		}
	}
	else if (turn.compare("black") == 0) {
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