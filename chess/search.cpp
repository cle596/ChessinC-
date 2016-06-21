#include <ctime>
#include <algorithm>
#include <map>
#include <bitset>

#include "search.h"
#include "node.h"

int
Search::ab(Node& n,int alpha,int beta,int d)
{
	int g, a, b;
	if (db.find(hash(n)) != db.end()) {
		if (n.a >= beta) return n.a;
		if (n.b <= alpha) return n.b;
		alpha = std::max(alpha, n.a);
		beta = std::min(beta, n.b);
	}
	if (d == 0) {
		g = n.score();
	}
	else if (n.turn == "white") {
		g = -inf; a = alpha;
		for (size_t x = 0; x < n.moves.size(); ++x) {
			while (g < beta) {
				Node nn = Node(n);
				nn.update_board(n.moves.at(x));
				nn.flips();
				g = std::max(g, ab(nn, a, beta, d - 1));
				a = std::max(a, g);
			}
		}
	}
	else {
		g = inf; b = beta;
		for (size_t x = 0; x < n.moves.size(); ++x) {
			while (g > alpha) {
				Node nn = Node(n);
				nn.update_board(n.moves.at(x));
				nn.flips();
				g = std::min(g, ab(nn, alpha, b, d - 1));
				if (d == depth &&
					g < b) {
					bmove = n.moves.at(x);
				}
				else {
					b = std::min(b, g);
				}
			}
		}
	}
	if (g <= alpha) {
		n.b = g;
		db[hash(n)] = n;
	}
	if (g > alpha && g < beta) {
		n.a = g;
		n.b = g;
		db[hash(n)] = n;
	}
	if (g >= beta) {
		n.a = g;
		db[hash(n)] = n;
	}
	return g;
}

int
Search::recurse(Node& n,int d,int max,int min)
{
	if (db.find(hash(n)) != db.end()) {
		if (n.a >= min) return n.a;
		if (n.b <= max) return n.b;
		max = std::max(max,n.a);
		min = std::min(min,n.b);
	}
	n.gen_moves();
	if (int(history.size()) > depth - d) {
		sort(n.moves, history.at(depth - d));
	}
	if (d > 0) {
		for (size_t x = 0; x < n.moves.size(); ++x) {
			Node nn = Node(n);
			nn.update_board(n.moves.at(x));
			nn.flips();
			nn.nscore = recurse(nn, d - 1, max, min);
			if (nn.nscore >= min && n.turn == "white") {
				return min;
			}
			else if (nn.nscore <= max && n.turn == "black") {
				return max;
			}
			else if (nn.nscore > max &&
				n.turn=="white") {
				max = nn.nscore;
			}
			else if (nn.nscore < min &&
				n.turn=="black") {
				min = nn.nscore;
				if (d == depth) {
					bmove.assign(n.moves.at(x));
				}
			}
		}
		if (n.turn == "white") {
			return max;
		}
		else{
			return min;
		}
	}
	else /*if (d == 0)*/ {
		n.nscore = n.score();
		db[hash(n)] = n;
		return n.nscore; 
	}
	//if ()
}

int Search::guess(Node& n,int g) {
	//int guess = 0;
	int inf = 100000;
	int upper = inf;
	int lower = -inf;
	int b = 0;
	while (lower < upper) {
		b = std::max(g, lower + 1);
		g = recurse(n, depth, b - 1, b);
		/*std::cout << "guess: " << g
			<< " upper: " << upper
			<< " lower: " << lower
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
	depth = 1;
	int inf = 100000;
	int g = 0;
	history.clear();
	while (depth <= max) {
		clock_t t = clock();
		std::cout << "depth: " << depth << std::endl;
		std::cout << "ab score: " << recurse(n, depth, -inf, inf) << std::endl;
		//g = guess(n,g);
		//std::cout << "guess: " << g << std::endl;
		std::cout << "best move: " << Game::pos_to_move(bmove) << std::endl;
		std::cout << "history: " << std::endl;
		for (size_t x = 0; x < history.size(); ++x) {
			std::cout << Game::pos_to_move(history.at(x)) << std::endl;
		}
		std::cout << "time: " << (clock() - t) / 1000.0 << std::endl << std::endl;
		/*
		if (int(history.size()) >= depth) {
			history.at(depth-1) = bmove;
		}
		else {
			history.push_back(bmove);
		}
		*/
		depth += 1;
	}
	if (depth > max) {
		depth -= 1;
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
	int z = 0;
	for (int x = 0; x < 120; ++x) {
		P_keymap[x] = z;
		N_keymap[x] = z + 120;
		B_keymap[x] = z + 120*2;
		R_keymap[x] = z + 120 * 3;
		Q_keymap[x] = z + 120 * 4;
		K_keymap[x] = z + 120 * 5;
		p_keymap[x] = z + 120 * 6;
		n_keymap[x] = z + 120 * 7;
		b_keymap[x] = z + 120 * 8;
		r_keymap[x] = z + 120 * 9;
		q_keymap[x] = z + 120 * 10;
		k_keymap[x] = z + 120 * 11;
		z += 1;
	}
	//std::cout << std::bitset< 16 >(k_keymap[119]).to_string << std::endl;
}

std::string
Search::hash(Node& n) {
	int hash = 0;
	for (size_t x = 0; x < n.board.length(); ++x) {
		if (n.board.at(x) == 'P') {
			hash |= P_keymap[x];
		}
		else if (n.board.at(x) == 'p') {
			hash |= p_keymap[x];
		}
		else if (n.board.at(x) == 'N') {
			hash |= N_keymap[x];
		}
		else if (n.board.at(x) == 'n') {
			hash |= n_keymap[x];
		}
		else if (n.board.at(x) == 'B') {
			hash |= B_keymap[x];
		}
		else if (n.board.at(x) == 'b') {
			hash |= b_keymap[x];
		}
		else if (n.board.at(x) == 'R') {
			hash |= R_keymap[x];
		}
		else if (n.board.at(x) == 'r') {
			hash |= r_keymap[x];
		}
		else if (n.board.at(x) == 'Q') {
			hash |= Q_keymap[x];
		}
		else if (n.board.at(x) == 'q') {
			hash |= q_keymap[x];
		}
		else if (n.board.at(x) == 'K') {
			hash |= K_keymap[x];
		}
		else if (n.board.at(x) == 'k') {
			hash |= k_keymap[x];
		}
	}
	return std::bitset<16>(hash).to_string();
}