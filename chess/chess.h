#pragma once

#include <string>
#include <vector>

std::vector<std::string>
gen_moves(std::string);

std::string 
add_space_to_board(std::string);

std::string
move_to_pos(std::string);

std::string
pos_to_move(std::string);

std::vector<std::string>
translate_moves(std::vector<std::string>);

std::string
new_board(std::string, std::string);

std::string init_board =
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