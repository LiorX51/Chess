#ifndef BISHOP_H
#define BISHOP_H

#include "Figure.h"
class Bishop : public Figure
{
	public:
		Bishop(std::string name, std::string start_pos, bool is_white);

		bool does_attack(std::string Point);
};
#endif
