#ifndef KNIGHT_H
#define KNIGHT_H

#include "Figure.h"

#define TWO_STEPS		 2
#define STEP			 1

class Knight : public Figure
{
	public:
		Knight(const std::string name, const std::string start_pos, const bool is_white);

		bool does_attack(const std::string Point);
};
#endif
