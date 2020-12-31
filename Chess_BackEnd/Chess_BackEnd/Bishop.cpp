#include "Bishop.h"

Bishop::Bishop(const std::string name, const std::string start_pos, const bool is_white) : Figure(name, start_pos, is_white)
{

}

bool Bishop::does_attack(const std::string Point)
{
	bool r_val = false;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);
	int xIncrement = 0;
	int yIncrement = 0;

	if (abs(this->currPos_X - dst_x) == abs(this->currPos_Y - dst_y))
	{
		//checkk all points in diaganale until dstPoint
		xIncrement = (dst_x - this->currPos_X) / (abs(dst_x - this->currPos_X));
		yIncrement = (dst_y - this->currPos_Y) / (abs(dst_y - this->currPos_Y));

		for (int i = 1; i < abs(this->currPos_X - dst_x); i++)
		{
			if (this->board_str[(this->currPos_X + xIncrement * i) + (this->currPos_Y + yIncrement * i) * ROW] != EMPTY)
			{
				r_val = false;
				return r_val; // stop loop
			}
		}

		if (this->isWhite() && islower(this->board_str[dst_x + dst_y * ROW]) ||
			(!this->isWhite() && !islower(this->board_str[dst_x + dst_y * ROW])))
		{//if white and dstPoint has black figure or the opposite
			r_val = true;
		}
	}
	return r_val;
}
