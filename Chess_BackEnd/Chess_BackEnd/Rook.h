#ifndef ROOK_H
#define ROOK_H

#include "Figure.h"
class Rook : public Figure
{
public:

	Rook(std::string name, std::string start_pos, bool is_white);

	bool does_attack(std::string Point);
};
#endif
