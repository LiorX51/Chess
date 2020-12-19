#ifndef KNIGHT_H
#define KNIGHT_H

#include "Figure.h"

#define TWO_STEPS		 2
#define STEP			 1

class Knight : public Figure
{
	public:
		Knight(std::string name, std::string start_pos, bool is_white);

		bool does_attack(std::string Point);
};
#endif
