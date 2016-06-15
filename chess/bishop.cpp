#include "node.h"

#define add_int_strings(x,y) std::to_string(x).append(std::to_string(y))
#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)

void
Node::bishop(int x) {
	for (int y = 0; y < 4; ++y) {
		int z = 1;
		while (this->board.at(x + z*Bmoves[y]) == '.' ||
			in_array(this->board.at(x + z*Bmoves[y]), this->foe)) {
			if (this->board.at(x + z*Bmoves[y]) == '.') {
				this->moves.push_back(
					add_int_strings(x, x + z*Bmoves[y])
				);
			}
			else if (in_array(this->board.at(x + z*Bmoves[y]), this->foe)) {
				this->moves.push_back(
					add_int_strings(x, x + z*Bmoves[y])
				);
				break;
			}
			z += 1;
		}
	}
}