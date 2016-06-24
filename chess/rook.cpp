#include "node.h"
#include "macros.h"

#define incr z*Rmoves[y]

void
Node::rook(int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (empty_or_foe(board.at(x + incr))) {
				moves.push_back(add_int_strings(x, x + incr));
			if (foe(board.at(x + incr))) {
				break;
			}
			z += 1;
		}
	}
}