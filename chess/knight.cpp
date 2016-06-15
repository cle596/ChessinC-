#include "node.h"
#include "macros.h"

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
