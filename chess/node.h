#pragma once

#include <string>
#include <vector>

class Node {

public:

	std::string board =
		"         \n"
		"         \n"
		" rnbqkbnr\n"
		" pppppppp\n"
		" ........\n"
		" ........\n"
		" ........\n"
		" ........\n"
		" PPPPPPPP\n"
		" RNBQKBNR\n"
		"         \n"
		"         \n";

	int nscore;

	std::string turn;
	bool castle[4]; //wk,wq,bk,bq
	static const std::string castle_input[4];
	int en_passant;

	static const int 
		up = -10, 
		dn = 10,
		lt = -1,
		rt = 1,
		Nmoves[],
		Bmoves[],
		Rmoves[],
		Kmoves[],
		P = 100,
		N = 320,
		B = 330,
		R = 500,
		Q = 900,
		K = 20000,
		pawn_pst[120],
		knight_pst[120],
		bishop_pst[120],
		rook_pst[120],
		queen_pst[120],
		king_pst[120];

	static int npawn_pst[120],
		nknight_pst[120],
		nbishop_pst[120],
		nrook_pst[120],
		nqueen_pst[120],
		nking_pst[120];

	char foe[6] = { 'p','n','b','r','q','k' };
	int dub[8] = { 81,82,83,84,85,86,87,88 },
		bdub[8] = {31,32,33,34,35,36,37,38},
		wdub[8] = { 81,82,83,84,85,86,87,88 };

	std::vector<std::string> moves;

	//constructor and copy constructor 
	Node();
	Node(const Node& n);

	void update_board(std::string);
	void print();

	//move generation functions
	void pawn(int);
	void knight(int);
	void bishop(int);
	void rook(int);
	void queen(int);
	void king(int);
	std::vector<std::string> gen_moves();

	//rotates pst for blackside
	static int* rotate_pst(const int*,int*);

	//eval function
	int score();

	//change node members for move generation on opposite side
	void flips();
	void flip_foe();
	void flip_turn();
	void flip_dub();

	//castle related functions for copy constructor
	void castle_reset();
	static void castle_copy(const bool*,bool*);
	
	static void set_npst();
};

