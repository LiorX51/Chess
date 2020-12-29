#include "Rook.h"

Rook::Rook(std::string name, std::string start_pos, bool is_white) : Figure(name, start_pos, is_white)
{
}

bool Rook::does_attack(std::string Point)
{
	bool r_val = true;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);
	int yIncrement = 0;
	int xIncrement = 0;
	int i = 0;

	if ((this->currPos_X != dst_x) || (this->currPos_Y != dst_y))
	{//if the rook moves in x or y
		if (this->currPos_X == dst_x)
		{// check if no piece is in the middle in x row
			yIncrement = (dst_y - this->currPos_Y) / (abs(dst_y - this->currPos_Y));

			for (i = this->currPos_Y + yIncrement; i != dst_y; i += yIncrement)
			{//check each square until the dstPoint
				if (this->board_str[this->currPos_X + i * ROW] != EMPTY)
				{//found piece in the middle of the way
					return false;
				}

			}
		}
		else if (this->currPos_Y == dst_y)
		{
			xIncrement = (dst_x - this->currPos_X) / (abs(dst_x - this->currPos_X));

			for (i = this->currPos_X + xIncrement; i != dst_x; i += xIncrement)
			{//check each square until the dstPoint
				if (this->board_str[i + this->currPos_Y * ROW] != EMPTY)
				{//found piece in the middle of the way
					return false;
				}

			}
		}
		else
		{
			r_val = false;
		}
	}
	else
	{
		r_val = false;
	}
	return r_val;
}
