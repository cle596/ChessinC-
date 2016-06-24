#include <ctime>
#include <algorithm>
#include <map>
#include <bitset>
#include <iterator>

#include "search.h"
#include "node.h"
#include "value.h"
#include "macros.h"

using namespace std;

Search::Search() {
	maps['P'] = P_keymap;
	maps['N'] = N_keymap;
	maps['B'] = B_keymap;
	maps['R'] = R_keymap;
	maps['Q'] = Q_keymap;
	maps['K'] = K_keymap;
	maps['p'] = p_keymap;
	maps['n'] = n_keymap;
	maps['b'] = b_keymap;
	maps['r'] = r_keymap;
	maps['q'] = q_keymap;
	maps['k'] = k_keymap;
	gen_keymap();
}

int
Search::retrieve(Node& n,int& alpha,int& beta,int& d,int& ret) {
	ret = inf * 2;
	if (in_tt(db, hash(n))) {
		Value v = db[hash(n)];
		if (v.d <= d) {
			if (v.a >= beta) ret=v.a;
			if (v.b <= alpha) ret=v.b;
			alpha = max(alpha, v.a);
			beta = min(beta, v.b);
		}
	}
	return ret;
}

void
Search::store(Node& n, int& alpha, int& beta, int& d,int& g) {
	if (g <= alpha) {
		n.b = g;
		if (not_in_tt(db, hash(n))) {
			db[hash(n)] = Value(-100000, n.b, d);
		}
		else {
			if (db[hash(n)].d <= d) {
				db[hash(n)].b = n.b;
				db[hash(n)].d = d;
			}
		}
	}
	if (g > alpha && g < beta) {
		n.a = g;
		n.b = g;
		if (not_in_tt(db, hash(n))) {
			db[hash(n)] = Value(n.a, n.b, d);
		}
		else {
			if (db[hash(n)].d <= d) {
				db[hash(n)].a = n.a;
				db[hash(n)].b = n.b;
				db[hash(n)].d = d;
			}
		}
	}
	if (g >= beta) {
		n.a = g;
		if (not_in_tt(db, hash(n))) {
			db[hash(n)] = Value(n.a, 100000, d);
		}
		else {
			if (db[hash(n)].d <= d) {
				db[hash(n)].a = n.a;
				db[hash(n)].d = d;
			}
		}
	}
}

int
Search::ab(Node& n,int alpha,int beta,int d)
{
	int g, a, b, c=0,ret;
	std::vector<Node> children;
	/*
	ret=retrieve(n,alpha,beta,d,ret);
	if (ret != inf * 2) {
		return ret;
	}
	*/
	if (d == 0) {
		g = n.score();
	}
	else if (n.turn == "white") {
		g = -inf; 
		a = alpha;
		n.gen_moves();
		while (c < int(n.moves.size()) && g < beta) {
			make_child(children, n, n.moves.at(c));
			g = max(g, ab(children.back(), a, beta, d - 1));
			a = max(a, g);
			c += 1;
		}
	}
	else {
		g = inf; 
		b = beta;
		n.gen_moves();
		while (c < int(n.moves.size()) && g > alpha) {
			make_child(children,n,n.moves.at(c));
			cout << children.back().turn << endl; // color not flipped!
			g = min(g, ab(children.back(), alpha, b, d - 1));
			if (d == depth) {
				if (g < b) {
					bmove = n.moves.at(c);
					b = g;
				}
			}
			else {
				b = min(b, g);
			}
			c += 1;
		}
	}
	//store(n, alpha, beta, d, g);
	return g;
}

void
Search::make_child(vector<Node>& children,Node& parent,string move) {
	children.push_back(Node(parent));
	children.back().update_board(move);
}

void 
Search::gen_keymap() {
	vector<char> keys;
	for (map<char, map<int, int>>::iterator it = maps.begin(); it != maps.end(); ++it) {
		keys.push_back(it->first);
	}
	for (int x = 0; x < 120; ++x) {
		for (size_t y = 0; y < keys.size(); ++y) {
			maps[keys.at(y)][x] = rand() % 2147483647;
		}
	}
}

int
Search::hash(Node& n) {
	int hash = 0;
	vector<char> keys;
	for (map<char, map<int, int>>::iterator it = maps.begin(); it != maps.end(); ++it) {
		keys.push_back(it->first);
	}
	for (size_t x = 0; x < n.board.length(); ++x) {
		for (size_t y = 0; y < keys.size(); ++y) {
			if (n.board.at(x) == keys.at(y)) {
				hash ^= maps[keys.at(y)][x];
			}
		}
	}
	return hash;
}