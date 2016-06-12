#pragma once

void
pawn(std::vector<std::string>&, std::string, int);

void
knight(std::vector<std::string>&, std::string, int);

void
bishop(std::vector<std::string>&, std::string, int);

void
rook(std::vector<std::string>&, std::string, int);

void
queen(std::vector<std::string>&, std::string, int);

void
king(std::vector<std::string>&, std::string, int);

std::vector<std::string>
gen_moves(std::string);



