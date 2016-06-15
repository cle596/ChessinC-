#include "node.h"
#include "macros.h"

#define incr z*Bmoves[y]

void
Node::bishop(int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (this->board.at(x + incr) == '.' ||
			in_array(this->board.at(x + incr), this->foe)) {
			if (this->board.at(x + incr) == '.') {
				this->moves.push_back(
					add_int_strings(x, x + incr)
				);
			}
			else if (in_array(this->board.at(x + incr), this->foe)) {
				this->moves.push_back(
					add_int_strings(x, x + incr)
				);
				break;
			}
			z += 1;
		}
	}
}