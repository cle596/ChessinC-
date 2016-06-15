#include "node.h"
#include "gendefs.h"

#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)

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
