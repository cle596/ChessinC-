#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "game.h"
#include "macros.h"

using namespace std;

Game::Game() {
	cout << "time\nto play\nchess!" << endl;
	Node::set_npst();
	for (int x = 0; x < 8; ++x) {
		mp_cols[97 + x] = 1 + x;
	}
	for (int x = 0; x < 8; ++x) {
		mp_rows[49 + x] = 90 - 10 * x;
	}
	for (int x = 0; x < 8; ++x) {
		pm_cols[1 + x] = 97 + x;
	}
	for (int x = 0; x < 8; ++x) {
		pm_rows[9 - x] = 49 + x;
	}
}

bool
Game::process_input() {
	root.gen_moves();
	if (in_vector(pos, root.moves)) {
		root.update_board(pos);
		root.moves.clear();
		return true;
	}
	else {
		cout << "not a legal move" << endl;
		return false;
	}
}

void
Game::take_input(string move) {
	cout << "make your move: ";
	while (true) {
		if (move == "") {
			cin >> input;
		}
		else {
			input = move;
		}
		if (input.length() == 4) {
			break;
		}
		else {
			cout << "not a legal move" << endl;
			cout << "make your move: ";
		}
	}
	if (in_array(input, Node::castle_input)) {
		pos = input;
	}
	else {
		pos = move_to_pos(input);
	}
}

string
Game::move_to_pos(string move) {
	string pos;
	for (int x = 0; x < 3; x += 2) {
		pos.append(
			to_string(
				mp_cols[move.at(x)] + 
				mp_rows[move.at(x + 1)]
			)
		);
	}
	return pos;
}

string
Game::pos_to_move(string pos) {
	string move;
	int p1 = stoi(pos.substr(0, 2), nullptr);
	int p2 = stoi(pos.substr(2, 2), nullptr);
	move += pm_cols.at(p1 - (p1 / 10) * 10);
	move += pm_rows.at(p1 / 10);
	move += pm_cols.at(p2 - (p2 / 10) * 10);
	move += pm_rows.at(p2 / 10);
	return move;
}

vector<string>
Game::translate_moves(vector<string> moves) {
	for (size_t x = 0; x < moves.size(); ++x) {
		tmoves.push_back(pos_to_move(moves.at(x)));
	}
	return tmoves;
}

