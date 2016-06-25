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

	Search();

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
	map<char, map<int,int>> maps;
	vector<char> keys;
	void gen_keymap();

	int hash(Node&);
	int retrieve(Node&n, int&, int&, int&,int&);
	void store(Node&, int&, int&, int&, int&);

	void make_child(vector<Node>&, Node&, string);
	int ab(Node&, int, int, int);

};