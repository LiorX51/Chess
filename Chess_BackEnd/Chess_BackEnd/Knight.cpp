#include "Knight.h"

Knight::Knight(std::string name, std::string start_pos, bool is_white) : Figure(name, start_pos, is_white)
{
}

bool Knight::does_attack(std::string Point)
{
	bool r_val = false;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);

	if ((abs(this->currPos_X - dst_x) == TWO_STEPS && abs(this->currPos_Y - dst_y) == STEP) || (abs(this->currPos_X - dst_x) == STEP && abs(this->currPos_Y - dst_y) == TWO_STEPS))
	{
		r_val = true;
	}
	return r_val;
}
