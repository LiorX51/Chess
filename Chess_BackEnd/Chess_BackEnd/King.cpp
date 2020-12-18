#include "King.h"

King::King(std::string name, std::string start_pos, bool is_white) : Figure(name, start_pos, is_white)
{
}

bool King::does_attack(std::string Point)
{
	bool r_val = false;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);

	if ((dst_y - this->currPos_Y == STEP || this->currPos_Y - dst_y == STEP) &&
		(dst_x - this->currPos_X == STEP || this->currPos_X - dst_x == STEP))
	{//if the king can move one step forword or backwards and left or right(1 step in diagonal)
		r_val = true;
	}

	return r_val;
}
