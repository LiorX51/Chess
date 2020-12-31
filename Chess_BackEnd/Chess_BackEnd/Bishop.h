#ifndef BISHOP_H
#define BISHOP_H

#include "Figure.h"
class Bishop : public Figure
{
	public:
		Bishop(const std::string name, const std::string start_pos, const bool is_white);

		bool does_attack(const std::string Point);
};
#endif
