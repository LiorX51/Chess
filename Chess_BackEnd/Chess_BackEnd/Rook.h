#ifndef ROOK_H
#define ROOK_H

#include "Figure.h"
class Rook : public Figure
{
public:

	Rook(const std::string name, const std::string start_pos, const bool is_white);

	bool does_attack(const std::string Point);
};
#endif
