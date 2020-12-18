#include "pawn.h"

Pawn::Pawn(std::string name, std::string start_pos, bool is_white) : Figure(name, start_pos, is_white)
{
}

bool Pawn::does_attack(std::string Point)
{
	bool r_val = false;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);

	if (isWhite())
	{//if white
		if ((this->currPos_Y - dst_y == STEP) &&
			(dst_x - this->currPos_X == STEP || this->currPos_X - dst_x == STEP))
		{//if the pawn moves one step forword and left or right(1 step in diagonal)
			r_val = true;
		}
	}
	else
	{// if black
		if ((dst_y - this->currPos_Y == STEP) &&
			(dst_x - this->currPos_X == STEP || this->currPos_X - dst_x == STEP))
		{//if the pawn moves one step forword and left or right(1 step in diagonal)
			r_val = true;
		}
	}
	return r_val;
}
