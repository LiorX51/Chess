#include "board.h"

board::board()
{
	int i = 0;

	board_str = "";
	for (i = 0; i < 64; i++)
	{
		board_figures[i] = nullptr;
	}
}

board::~board()
{
	int i = 0;
	
	while (board_figures[i] != nullptr)
	{
		delete (board_figures[i]);
		i++;
	}
	delete[] board_figures;
}

std::string board::get_board()
{
    return this->board_str;
}

void board::set_board_figures()
{
    int len = this->board_str.length();
	int i = 0;
	int j = 0;
	std::string pos = "";

	for (j = 0; (i + j * ROW) < len; j++)
	{
		for (i = 0; i < ROW; i++)
		{
			pos = "";
			pos.append(1,('a' + i));
			pos.append(1,'0'+(ROW - j));

			switch (tolower(this->board_str[i + j*ROW]))
			{
				std::cout << pos << std::endl;
				case 'p':
				{
					// create a new pawn and place it in the write place;
					this->board_figures[i + j * ROW] = new Pawn("p", pos, !islower(this->board_str[i + j * ROW]));
					break;
				}
				default:
					this->board_figures[i + j * ROW] = nullptr;
					break;
				}
		}
	}
}

bool board::is_chess(std::string figure_pos)
{
	int index = 0;
	std::string king_pos = "";
	int figure_x = Figure::get_tran_x(figure_pos);
	int figure_y = Figure::get_tran_y(figure_pos);
	Figure* moved_figure = this->board_figures[figure_x + figure_y * ROW];

	if (moved_figure->isWhite())
	{// if white need to check chess of black king

		//find black king's pos:
		index = this->board_str.find(BLACK_KING);
	}
	else
	{// if black need to check chess of white king
		
		//find white king's pos:
		index = this->board_str.find(WHITE_KING);
	}

	//king of choice pos
	king_pos = this->board_figures[index]->currPos;

	return moved_figure->does_attack(king_pos); //call the figure's func to check if threats the king
}

bool board::move_pawn(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	Figure& curr = *this->board_figures[src_x + src_y * ROW];
	bool r_val = false;
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);

	if (this->board_str[dst_x + dst_y * ROW] != EMPTY)
	{// need to check if can eat what is in dstPoint
		if (curr.isWhite() && islower(this->board_str[dst_x + dst_y * ROW]))
		{//if white and dstPoint has black figure
			if ((curr.currPos_Y - dst_y == STEP) &&
				(dst_x - curr.currPos_X == STEP || curr.currPos_Y - dst_y == STEP))
			{//if the pawn moves one step forword and left or right(1 step in diagonal)
				r_val = true;
			}
		}
		else if (!curr.isWhite() && !islower(this->board_str[dst_x + dst_y * ROW]))
		{// if black && eats white figure
			if ((dst_y - curr.currPos_Y == STEP) &&
				(dst_x - curr.currPos_X == STEP || curr.currPos_Y - dst_y == STEP))
			{//if the pawn moves one step forword and left or right(1 step in diagonal)
				r_val = true;
			}
		}
		//move the piece if needed and delete the eatten piece
		if (r_val)
		{
			delete(this->board_figures[dst_x + dst_y * ROW]);
			this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
			this->board_figures[src_x + src_y * ROW] = nullptr;
		}
	}
	else
	{// need to check if pawn can move to empty place
		if ((curr.currPos_Y == START_LINE_BLACK || curr.currPos_Y == START_LINE_WHITE) && curr.currPos_X == dst_x)
		{// if the pawn is in start line he can move 2 steps
			if (curr.isWhite())
			{//if white
				if ((curr.currPos_Y - dst_y == TWO_STEPS) || (curr.currPos_Y - dst_y == STEP))
				{//if the action is one or two steps
					r_val = true;
				}
			}
			else
			{// if black
				if ((dst_y - curr.currPos_Y == TWO_STEPS) || (dst_y - curr.currPos_Y == STEP))
				{//if the action is one or two steps
					r_val = true;
				}
			}
		}
		else
		{// the pawn can move 1 step
			if (curr.isWhite())
			{//if white
				if (dst_y - curr.currPos_Y == STEP)
				{//if the action is one step
					r_val = true;
				}
			}
			else
			{
				if (curr.currPos_Y - dst_y == STEP)
				{//if the action is one step
					r_val = true;
				}
			}
		}
		//move the piece if needed
		if (r_val)
		{
			this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
			this->board_figures[src_x + src_y * ROW] = nullptr;
		}
	}
	return r_val;
}
