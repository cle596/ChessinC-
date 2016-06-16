#include "node.h"
#include "macros.h"

#define incr z*Rmoves[y]

void
Node::rook(int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (board.at(x + incr) == '.' ||
			in_array(board.at(x + incr), foe)) {
			if (board.at(x + incr) == '.') {
				moves.push_back(
					add_int_strings(x, x + incr)
				);
			}
			else if (in_array(board.at(x + incr), foe)) {
				moves.push_back(
					add_int_strings(x, x + incr)
				);
				break;
			}
			z += 1;
		}
	}
}