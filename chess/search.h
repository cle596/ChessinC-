#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "game.h"
#include "value.h"

class Search {
public:

	std::string bmove;
	std::map<int,Value> db;
	std::vector<std::string> history;
	int depth;
	static const int inf = 100000;
	std::map<int, int>
		P_keymap, p_keymap,
		N_keymap, n_keymap,
		B_keymap, b_keymap,
		R_keymap, r_keymap,
		Q_keymap, q_keymap,
		K_keymap, k_keymap;
	
	int guess(Node&,int);
	void tcurse(Node&);
	void sort(std::vector<std::string>& moves, std::string move);
	void gen_keymap();
	int hash(Node&);
	int ab(Node&, int, int, int);
};