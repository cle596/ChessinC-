#include "node.h"
#include "macros.h"

void
Node::knight(int x) {
	for (int y = 0; y < 8; ++y) {
		if (board.at(x + Nmoves[y]) == '.' ||
			in_array(board.at(x + Nmoves[y]), foe)) {
			moves.push_back(add_int_strings(x, x + Nmoves[y]));
		}
	}
}
