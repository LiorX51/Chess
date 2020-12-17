#include "pawn.h"

Pawn::Pawn(std::string name, std::string start_pos, bool is_white) : Figure(name, start_pos, is_white)
{
}

bool Pawn::can_move(std::string dstPoint)
{
	bool r_val = false;
	int dst_x = get_tran_x(dstPoint);
	int dst_y = get_tran_y(dstPoint);

	if (this->board_str[dst_x + dst_y*8] != EMPTY)
	{// need to check if can eat what is in dstPoint
		if (isWhite() && !islower(this->board_str[dst_x + dst_y * 8]))
		{//if white and dstPoint has black figure
			if ((this->currPos_Y - dst_y == STEP) &&
				(dst_x - this->currPos_X == STEP || this->currPos_Y - dst_y == STEP))
			{//if the pawn moves one step forword and left or right(1 step in diagonal)
				r_val = true;
			}
		}
		else if(!isWhite() && islower(this->board_str[dst_x + dst_y * 8]))
		{// if black && eats white figure
			if ((dst_y - this->currPos_Y == STEP) &&
				(dst_x - this->currPos_X == STEP || this->currPos_Y - dst_y == STEP))
			{//if the pawn moves one step forword and left or right(1 step in diagonal)
				r_val = true;
			}
		}
	}
	else
	{// need to check if pawn can move to empty place
		if ((this->currPos_Y == START_LINE_BLACK || this->currPos_Y == START_LINE_WHITE) && this->currPos_X == dst_x)
		{// if the pawn is in start line he can move 2 steps
			if (isWhite())
			{//if white
				if ((this->currPos_Y - dst_y == TWO_STEPS) || (this->currPos_Y - dst_y == STEP))
				{//if the action is one or two steps
					r_val = true;
				}
			}
			else
			{// if black
				if ((dst_y - this->currPos_Y == TWO_STEPS) || (dst_y - this->currPos_Y == STEP))
				{//if the action is one or two steps
					r_val = true;
				}
			}
		}
		else
		{// the pawn can move 1 step
			if (isWhite())
			{//if white
				if (dst_y - this->currPos_Y == STEP)
				{//if the action is one step
					r_val = true;
				}
			}
			else
			{
				if (this->currPos_Y - dst_y == STEP)
				{//if the action is one step
					r_val = true;
				}
			}
		}
	}
	return r_val;
	
}

bool Pawn::does_attack(std::string Point)
{
	bool r_val = false;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);

	if (isWhite())
	{//if white
		if ((this->currPos_Y - dst_y == STEP) &&
			(dst_x - this->currPos_X == STEP || this->currPos_Y - dst_y == STEP))
		{//if the pawn moves one step forword and left or right(1 step in diagonal)
			r_val = true;
		}
	}
	else
	{// if black
		if ((dst_y - this->currPos_Y == STEP) &&
			(dst_x - this->currPos_X == STEP || this->currPos_Y - dst_y == STEP))
		{//if the pawn moves one step forword and left or right(1 step in diagonal)
			r_val = true;
		}
	}
	return r_val;
}
