#include "Queen.h"

Queen::Queen(std::string name, std::string start_pos, bool is_white) : Figure(name, start_pos, is_white)
{
}

bool Queen::does_attack(std::string Point)
{
	bool r_val = true;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);

	int yIncrement = 0;
	int xIncrement = 0;

	if (this->currPos_X != dst_x || this->currPos_Y != dst_y)
	{

		if (this->currPos_X == dst_x)
		{
			yIncrement = (dst_y - this->currPos_Y) / (abs(dst_y - this->currPos_Y));
			for (int i = this->currPos_Y + yIncrement; i != dst_y; i += yIncrement)
			{
				if (this->board_str[dst_x + i * ROW] != EMPTY)
				{
					return false;
				}
			}
		}
		else
			if (this->currPos_Y == dst_y)
			{

				xIncrement = (dst_x - this->currPos_X) / (abs(dst_x - this->currPos_X));
				for (int i = this->currPos_Y + xIncrement; i != dst_x; i += xIncrement)
				{
					if (this->board_str[i + dst_y * ROW] != EMPTY)
					{
						return false;
					}
				}
			}
			else
				if (abs(this->currPos_X - dst_x) == abs(this->currPos_Y - dst_y))
				{
					xIncrement = (dst_x - this->currPos_X) / (abs(dst_x - this->currPos_X));
					yIncrement = (dst_y - this->currPos_Y) / (abs(dst_y - this->currPos_Y));

					for (int i = 1; i < abs(this->currPos_X - dst_x); i++)
					{
						if (this->board_str[this->currPos_X + xIncrement * i + (this->currPos_Y + yIncrement * i) * ROW] != EMPTY)
						{
							return false;
						}
					}
				}
				else
				{
					return false;
				}
	}
	return r_val;

}
