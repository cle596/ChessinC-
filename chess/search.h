#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "game.h"

class Search {
public:

	std::string bmove;
	std::map<std::string,Node> db;
	std::vector<std::string> history;
	int depth;
	std::map<int, int>
		P_keymap, p_keymap,
		N_keymap, n_keymap,
		B_keymap, b_keymap,
		R_keymap, r_keymap,
		Q_keymap, q_keymap,
		K_keymap, k_keymap;
	
	int recurse(Node&,int,int,int);
	int guess(Node&,int);
	void tcurse(Node&);
	void sort(std::vector<std::string>& moves, std::string move);
	void gen_keymap();
	std::string hash(Node&);
};