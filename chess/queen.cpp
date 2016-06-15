#include "node.h"

#define add_int_strings(x,y) std::to_string(x).append(std::to_string(y))
#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)

void
Node::queen(int x) {
	for (int y = 0; y < 8; ++y) {
		int z = 1;
		while (this->board.at(x + z*Kmoves[y]) == '.' ||
			in_array(this->board.at(x + z*Kmoves[y]), this->foe)) {
			if (this->board.at(x + z*Kmoves[y]) == '.') {
				this->moves.push_back(
					add_int_strings(x, x + z*Kmoves[y])
				);
			}
			else if (in_array(this->board.at(x + z*Kmoves[y]), this->foe)) {
				this->moves.push_back(
					add_int_strings(x, x + z*Kmoves[y])
				);
				break;
			}
			z += 1;
		}
	}
}