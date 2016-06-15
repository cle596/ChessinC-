#include "node.h"
#include "macros.h"

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
			this->board.substr(96,2) == "..") {
			this->moves.push_back("wk00");
		}
		if (this->castle[1] &&
			this->board.substr(92,3) == "...") {
			this->moves.push_back("wq00");
		}
	}
	else if (this->turn.compare("black") == 0) {
		if (this->castle[2] &&
			this->board.substr(26,2) == "..") {
			this->moves.push_back("bk00");
		}
		if (this->castle[3] &&
			this->board.substr(22,3) == "...") {
			this->moves.push_back("bq00");
		}
	}
}