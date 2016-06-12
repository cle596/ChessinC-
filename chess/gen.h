#pragma once

std::vector<std::string>
pawn(std::vector<std::string>, std::string, int);

std::vector<std::string>
knight(std::vector<std::string>, std::string, int);

std::vector<std::string>
bishop(std::vector<std::string>, std::string, int);

std::vector<std::string>
rook(std::vector<std::string>, std::string, int);

std::vector<std::string>
queen(std::vector<std::string>, std::string, int);

std::vector<std::string>
gen_moves(std::string);

