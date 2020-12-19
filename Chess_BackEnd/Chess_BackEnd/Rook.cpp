#include "Rook.h"

Rook::Rook(std::string name, std::string start_pos, bool is_white) : Figure(name, start_pos, is_white)
{
}

bool Rook::does_attack(std::string Point)
{
	bool r_val = false;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);

	if ((this->currPos_X == dst_x) && (this->currPos_Y != dst_y) ||
		(this->currPos_X != dst_x) && (this->currPos_Y == dst_y))
	{//if the rook can move in x or y
		r_val = true;
	}
	return r_val;
}
