#include <ctime>
#include <algorithm>
#include <map>
#include <bitset>

#include "search.h"
#include "node.h"
#include "value.h"
#include "macros.h"

using namespace std;

int
Search::ab(Node& n,int alpha,int beta,int d)
{
	int g, a, b;
	if (in_tt(db,hash(n))) {
		Value v = db[hash(n)];
		if (v.d <= d) {
			if (v.a >= beta) return v.a;
			if (v.b <= alpha) return v.b;
			alpha = max(alpha, v.a);
			beta = min(beta, v.b);
		}
	}
	if (d == 0) {
		g = n.score();
	}
	else if (n.turn == "white") {
		g = -inf; 
		a = alpha;
		n.gen_moves();
		int c = 0;
		vector<Node> children;
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
		int c = 0;
		std::vector<Node> children;
		while (c < int(n.moves.size()) && g > alpha) {
			make_child(children,n,n.moves.at(c));
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
	
	if (g <= alpha) {
		n.b = g;
		if (not_in_tt(db,hash(n))) {
			db[hash(n)] = Value(-100000, n.b,d);
		}
		else {
			if (db[hash(n)].d >= d) {
				db[hash(n)].b = n.b;
				db[hash(n)].d = d;
			}
		}
	}
	if (g > alpha && g < beta) {
		n.a = g;
		n.b = g;
		if (not_in_tt(db,hash(n))) {
			db[hash(n)] = Value(n.a, n.b,d);
		}
		else {
			if (db[hash(n)].d >= d) {
				db[hash(n)].a = n.a;
				db[hash(n)].b = n.b;
				db[hash(n)].d = d;
			}
		}
	}
	if (g >= beta) {
		n.a = g;
		if (not_in_tt(db,hash(n))) {
			db[hash(n)] = Value(n.a, 100000, d);
		}
		else {
			if (db[hash(n)].d >= d) {
				db[hash(n)].a = n.a;
				db[hash(n)].d = d;
			}
		}
	}
	return g;
}

void
Search::make_child(vector<Node>& children,Node& parent,string move) {
	children.push_back(Node(parent));
	children.back().update_board(move);
}

int 
Search::guess(Node& n,int g) {
	int upper = inf;
	int lower = -inf;
	int b = 0;
	while (lower < upper) {
		g = (upper + lower + 1) / 2;
		b = max(g, lower + 1);
		g = ab(n, b - 1, b,depth);
		if (g < b) {
			upper = g;
		}
		else {
			lower = g;
		}
	}
	return g;
}

void 
Search::tcurse(Node& n) {
	int max = depth;
	depth = 1;
	int g = 0;
	history.clear();
	while (depth <= max) {
		clock_t t = clock();
		g = guess(n, g);
		n.moves.clear();
		depth += 1;
	}
	if (depth > max) {
		depth -= 1;
	}
	if (depth == max) {
		cout << "best move: " << Game::pos_to_move(bmove) << endl;
	}
}

void
Search::sort(vector<string>& moves,string move) {
	for (size_t x = 0; x < moves.size(); ++x) {
		if (moves.at(x) == move) {
			moves.at(x) = moves.at(0);
			moves.at(0) = move;
			return;
		}
	}
}

void 
Search::gen_keymap() {
	for (int x = 0; x < 120; ++x) {
		P_keymap[x] = rand() % 2147483647;
		N_keymap[x] = rand() % 2147483647;
		B_keymap[x] = rand() % 2147483647;
		R_keymap[x] = rand() % 2147483647;
		Q_keymap[x] = rand() % 2147483647;
		K_keymap[x] = rand() % 2147483647;
		p_keymap[x] = rand() % 2147483647;
		n_keymap[x] = rand() % 2147483647;
		b_keymap[x] = rand() % 2147483647;
		r_keymap[x] = rand() % 2147483647;
		q_keymap[x] = rand() % 2147483647;
		k_keymap[x] = rand() % 2147483647;
	}
}

int
Search::hash(Node& n) {
	int hash = 0;
	for (size_t x = 0; x < n.board.length(); ++x) {
		if (n.board.at(x) == 'P') {
			hash ^= P_keymap[x];
		}
		else if (n.board.at(x) == 'p') {
			hash ^= p_keymap[x];
		}
		else if (n.board.at(x) == 'N') {
			hash ^= N_keymap[x];
		}
		else if (n.board.at(x) == 'n') {
			hash ^= n_keymap[x];
		}
		else if (n.board.at(x) == 'B') {
			hash ^= B_keymap[x];
		}
		else if (n.board.at(x) == 'b') {
			hash ^= b_keymap[x];
		}
		else if (n.board.at(x) == 'R') {
			hash ^= R_keymap[x];
		}
		else if (n.board.at(x) == 'r') {
			hash ^= r_keymap[x];
		}
		else if (n.board.at(x) == 'Q') {
			hash ^= Q_keymap[x];
		}
		else if (n.board.at(x) == 'q') {
			hash ^= q_keymap[x];
		}
		else if (n.board.at(x) == 'K') {
			hash ^= K_keymap[x];
		}
		else if (n.board.at(x) == 'k') {
			hash ^= k_keymap[x];
		}
	}
	return hash;
}