#ifndef KING_H
#define KING_H

#include "Figure.h"

#define STEP			 1

class King : public Figure
{
	public:
		King(const std::string name, const std::string start_pos, const bool is_white);

		bool does_attack(const std::string Point);
};
#endif
