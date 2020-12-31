#pragma once
#include "Figure.h"

class Queen : public Figure
{
	public:
		Queen(const std::string name, const std::string start_pos, const bool is_white);

		bool does_attack(const std::string Point);
};

