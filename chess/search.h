#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "game.h"
#include "value.h"
#include "macros.h"

using namespace std;

class Search {
public:

	string bmove;
	map<int,Value> db;
	vector<string> history;
	int depth;
	map<int, int>
		P_keymap, p_keymap,
		N_keymap, n_keymap,
		B_keymap, b_keymap,
		R_keymap, r_keymap,
		Q_keymap, q_keymap,
		K_keymap, k_keymap;
	
	int guess(Node&,int);
	void tcurse(Node&);
	void sort(vector<string>& moves, string move);
	void gen_keymap();
	int hash(Node&);
	int ab(Node&, int, int, int);
	void make_child(vector<Node>&, Node&, string);
	void retrieve(Node&n, int&, int&, int&);
	void store(Node&, int&, int&, int&, int&);
};