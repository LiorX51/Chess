#ifndef PAWN_H
#define PAWN_H

#include "Figure.h"

#define START_LINE_WHITE 6
#define START_LINE_BLACK 1
#define TWO_STEPS		 2
#define STEP			 1

class Pawn : public Figure
{
	public:

		Pawn(const std::string name, const std::string start_pos, const bool is_white);

		bool does_attack(const std::string Point);
};
#endif
