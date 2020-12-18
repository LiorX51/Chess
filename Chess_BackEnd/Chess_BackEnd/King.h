#ifndef KING_H
#define KING_H

#include "Figure.h"

#define STEP			 1

class King : public Figure
{
	public:
		King(std::string name, std::string start_pos, bool is_white);

		bool does_attack(std::string Point);
};
#endif
