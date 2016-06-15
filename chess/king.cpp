#include "node.h"

#define add_int_strings(x,y) std::to_string(x).append(std::to_string(y))
#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)

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
	else if (this->turn.compare("black") == 0) {
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