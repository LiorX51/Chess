#pragma once
#include "Figure.h"

class Queen : public Figure
{
	public:
		Queen(std::string name, std::string start_pos, bool is_white);

		bool does_attack(std::string Point);
};

