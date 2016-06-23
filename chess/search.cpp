#include <ctime>
#include <algorithm>
#include <map>
#include <bitset>

#include "search.h"
#include "node.h"
#include "value.h"

int
Search::ab(Node& n,int alpha,int beta,int d)
{
	int g, a, b;
	
	if (db.find(hash(n)) != db.end()) {
		//std::cout << v.a << " " << v.b << std::endl;
		if (db[hash(n)].d >= d) {
			if (db[hash(n)].a >= beta) return db[hash(n)].a;
			if (db[hash(n)].b <= alpha) return db[hash(n)].b;
			alpha = std::max(alpha, db[hash(n)].a);
			beta = std::min(beta, db[hash(n)].b);
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
		std::vector<Node> children;
		while (c < int(n.moves.size()) && g < beta) {
			children.push_back(Node(n));
			children.back().update_board(n.moves.at(c)); children.back().flips();
			g = std::max(g, ab(children.back(), a, beta, d - 1));
			a = std::max(a, g);
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
			children.push_back(Node(n));
			children.back().update_board(n.moves.at(c)); children.back().flips();
			g = std::min(g, ab(children.back(), alpha, b, d - 1));
			if (d == depth &&
				g < b) {
				std::cout << depth << std::endl; // this is never coming out as more than one
				bmove = n.moves.at(c);
				b = g;
			}
			else {
				b = std::min(b, g);
			}
			c += 1;
		}
	}
	
	if (g <= alpha) {
		n.b = g;
		if (db.find(hash(n)) == db.end()) {
			db[hash(n)] = Value(-100000, n.b,d);
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
		if (db.find(hash(n)) == db.end()) {
			db[hash(n)] = Value(n.a, n.b,d);
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
		if (db.find(hash(n)) == db.end()) {
			db[hash(n)] = Value(n.a, 100000, d);
		}
		else {
			if (db[hash(n)].d <= d) {
				db[hash(n)].a = n.a;
				db[hash(n)].d = d;
			}
		}
	}
	
	return g;
}

int Search::guess(Node& n,int g) {
	int inf = 100000;
	int upper = inf;
	int lower = -inf;
	int b = 0;
	while (lower < upper) {
		b = std::max(g, lower + 1);
		g = ab(n, b - 1, b,depth);
		std::cout << "guess: " << g << std::endl;
		/*std::cout << "guess: " << g
			<< " upper: " << upper
			<< " lower: " << lower
			<< " depth: " << depth
			<< std::endl;*/
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
	//std::cout << max << std::endl;
	depth = 1;
	int inf = 100000;
	int wg = 0; int bg = 0;
	history.clear();
	bool turn = false;
	while (depth <= max) {
		clock_t t = clock();
		if (turn) {
			wg = guess(n, wg);
		}
		else {
			bg = guess(n, bg);
		}
		n.moves.clear();
		depth += 1;
		turn = !turn;
	}
	if (depth > max) {
		depth -= 1;
	}
	if (depth == max) {
		std::cout << "best move: " << Game::pos_to_move(bmove) << std::endl;
	}
}

void
Search::sort(std::vector<std::string>& moves,std::string move) {
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