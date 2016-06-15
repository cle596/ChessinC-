#include "node.h"

#define add_int_strings(x,y) std::to_string(x).append(std::to_string(y))
#define in_vector(e,vec) std::find(vec.begin(), vec.end(), e) != vec.end()
#define in_array(e,arr) std::find(std::begin(arr), std::end(arr), e) != std::end(arr)

void
Node::pawn(int x) {
	static int di;
	if (this->turn.compare("white") == 0) {
		di = up;
	}
	else if (this->turn.compare("black") == 0) {
		di = dn;
	}
	if (this->board.at(x + di) == '.') {
		this->moves.push_back(
			add_int_strings(x, x + di)
		);
		if (in_array(x, this->dub) &&
			this->board.at(x + 2 * di) == '.') {
			this->moves.push_back(
				add_int_strings(x, x + 2 * di)
			);
		}
	}
	//cross
	if (in_array(this->board.at(x + di + rt), this->foe)) {
		this->moves.push_back(
			add_int_strings(x, x + di + rt)
		);
	}
	if (in_array(this->board.at(x + di + lt), this->foe)) {
		this->moves.push_back(
			add_int_strings(x, x + di + lt)
		);
	}
	//en passant
	if (x + di + rt == this->en_passant) {
		this->moves.push_back(
			add_int_strings(x, x + di + rt)
		);
	}
	if (x + di + lt == this->en_passant) {
		this->moves.push_back(
			add_int_strings(x, x + di + lt)
		);
	}
}
