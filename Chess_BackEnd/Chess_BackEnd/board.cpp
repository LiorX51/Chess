#include "board.h"

board::board()
{
	int i = 0;

	board_str = "";
	for (i = 0; i < 64; i++)
	{
		board_figures[i] = nullptr;
	}
	is_turn_white = true;
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

void board::switch_positions(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);
	char temp = 'a';
	
    //move the figure
	if (this->board_figures[dst_x + dst_y * ROW] != nullptr)
	{
		delete(this->board_figures[dst_x + dst_y * ROW]);
		this->board_str[dst_x + dst_y * ROW] = EMPTY;
	}

	this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
	this->board_figures[src_x + src_y * ROW] = nullptr;

	// set new params
	this->board_figures[dst_x + dst_y * ROW]->setX(dst_x);
	this->board_figures[dst_x + dst_y * ROW]->setY(dst_y);
	this->board_figures[dst_x + dst_y * ROW]->set_pos(dstPoint);

	// change the string of the board
	temp = this->board_str[src_x + src_y * ROW];
	this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
	this->board_str[dst_x + dst_y * ROW] = temp;
}

std::string board::get_board()
{
    return this->board_str;
}

void board::set_board_figures()
{
	int i = 0;
	int j = 0;
	std::string pos = "";
	std::string name = "";

	for (j = 0; j < ROW; j++)
	{
		for (i = 0; i < ROW; i++)
		{
			pos = "";
			pos.append(1,('a' + i));
			pos.append(1,'0'+(ROW - j));
			name = std::string(1, (this->board_str[i + j * ROW]));

			switch (tolower(this->board_str[i + j*ROW]))
			{
				case 'p':
				{
					// create a new pawn and place it in the write place;
					this->board_figures[i + j * ROW] = new Pawn(name, pos, !islower(this->board_str[i + j * ROW]));
					break;
				}
				case 'k':
				{
					// create a new king and place it in the write place;
					this->board_figures[i + j * ROW] = new King(name, pos, !islower(this->board_str[i + j * ROW]));
					break;
				}
				case 'r':
				{
					// create a new rook and place it in the write place;
					this->board_figures[i + j * ROW] = new Rook(name, pos, !islower(this->board_str[i + j * ROW]));
					break;
				}
				case 'b':
				{
					// create a new bishop and place it in the write place;
					this->board_figures[i + j * ROW] = new Bishop(name, pos, !islower(this->board_str[i + j * ROW]));
					break;
				}
				case 'n':
				{
					// create a new knight and place it in the write place;
					this->board_figures[i + j * ROW] = new Knight(name, pos, !islower(this->board_str[i + j * ROW]));
					break;
				}
				case 'q':
				{
					// create a new queen and place it in the write place;
					this->board_figures[i + j * ROW] = new Queen(name, pos, !islower(this->board_str[i + j * ROW]));
					break;
				}
				default:
				{
					this->board_figures[i + j * ROW] = nullptr;
					break;
				}
			}
		}
	}
}

void board::set_board_str()
{
	int i = 0;
	int j = 0;
	Figure* curr_figure = nullptr;
	for (j = 0; j < ROW; j++)
	{
		for (i = 0; i < ROW; i++)
		{
			curr_figure = this->board_figures[i + j * ROW];
			if (curr_figure != nullptr)
			{
				curr_figure->board_str = get_board();
			}
		}
	}
}

bool board::is_chess(std::string figure_pos)
{
	int black_index = 0;
	int white_index = 0;
	std::string white_king_pos = "";
	std::string black_king_pos = "";
	std::string curr_pos = "";
	int figure_x = Figure::get_tran_x(figure_pos);
	int figure_y = Figure::get_tran_y(figure_pos);
	Figure* curr_figure = this->board_figures[figure_x + figure_y * ROW];
	int i = 0;
	int j = 0;
	bool is_chess = false;

	//find black king's pos:
	black_index = this->board_str.find(BLACK_KING);
		
	//find white king's pos:
	white_index = this->board_str.find(WHITE_KING);

	//black king pos
	black_king_pos = this->board_figures[black_index]->currPos;

	//white king pos
	white_king_pos = this->board_figures[white_index]->currPos;
	
	// if figure is white
	if (curr_figure->isWhite())
	{	
		// need to check if moved figure blocks the possible chess of the other user
		for (j = 0; j < ROW; j++)
		{
			for (i = 0; i < ROW; i++)
			{
				curr_figure = this->board_figures[i + j * ROW];

				// if figures are not the same color and does attack the king:
				if (curr_figure != nullptr && // if figure not null
					curr_figure->isWhite() != this->board_figures[white_index]->isWhite() && // if are not the same color
					curr_figure->does_attack(white_king_pos)) // // if can move to king pos -> attacks the king
				{// there is a chess, return false
					is_chess = true;
					this->curr_msg_to_graphics = '4'; // move made doesn't block chess from other player
					return is_chess;
				}
			}
		}

		//check if moved figure made chess
		for (j = 0; j < ROW; j++)
		{
			for (i = 0; i < ROW; i++)
			{
				curr_figure = this->board_figures[i + j * ROW];

				// if figures are not the same color and does attack the king:
				if (curr_figure != nullptr && // if figure not null
					curr_figure->isWhite() != this->board_figures[black_index]->isWhite() && // if are not the same color
					curr_figure->does_attack(black_king_pos)) // if attacks the king
				{// there is a chess, return false
					is_chess = true;
					this->curr_msg_to_graphics = '1'; // move made chess on other player
					return is_chess;
				}
			}
		}
	}
	else // if figure is black
	{
		// need to check if moved figure blocks the possible chess of the other user
		for (j = 0; j < ROW; j++)
		{
			for (i = 0; i < ROW; i++)
			{
				curr_figure = this->board_figures[i + j * ROW];

				// if figures are not the same color and does attack the king:
				if (curr_figure != nullptr && // if figure not null
					curr_figure->isWhite() != this->board_figures[black_index]->isWhite() && // if are not the same color
					curr_figure->does_attack(black_king_pos)) // // if can move to king pos -> attacks the king
				{// there is a chess, return false
					is_chess = true;
					this->curr_msg_to_graphics = '4'; // move made doesn't block chess from other player
					return is_chess;
				}
			}
		}

		//check if moved figure made chess
		for (j = 0; j < ROW; j++)
		{
			for (i = 0; i < ROW; i++)
			{
				curr_figure = this->board_figures[i + j * ROW];

				// if figures are not the same color and does attack the king:
				if (curr_figure != nullptr && // if figure not null
					curr_figure->isWhite() != this->board_figures[white_index]->isWhite() && // if are not the same color
					curr_figure->does_attack(white_king_pos)) // if attacks the king
				{// there is a chess, return false
					is_chess = true;
					this->curr_msg_to_graphics = '1'; // move made chess on other player
					return is_chess;
				}
			}
		}
	}
	return is_chess;
}

bool board::move_figure(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);
	bool r_val = false;
	
	if (!islower(this->board_str[src_x + src_y * ROW]) != this->is_turn_white) // if the same color -> low letter is black color
	{
		this->curr_msg_to_graphics = '2'; // not your figure
		return false;
	}

	//if points are the same
	if (srcPoint == dstPoint)
	{
		this->curr_msg_to_graphics = '7'; // srcPoint and dstPoint are the same
		return false;
	}

	// if there is no figure
	if (this->board_str[src_x + src_y * ROW] == EMPTY)
	{
		this->curr_msg_to_graphics = '2'; // no figure in this pos
		return false;
	}

	// if the dst and src are not the same color
	if (this->board_str[dst_x + dst_y * ROW] == EMPTY ||
		islower(this->board_str[src_x + src_y * ROW]) != islower(this->board_str[dst_x + dst_y * ROW]))
	{
		// call the needed move functin based on the name of the figure
		switch (tolower(this->board_str[src_x + src_y * ROW]))
		{
			case 'p':
			{// a pawn
				r_val = move_pawn(srcPoint, dstPoint);
				break;
			}
			case 'k':
			{// a king
				r_val = move_king(srcPoint, dstPoint);
				break;
			}
			case 'r':
			{// a rook
				r_val = move_rook(srcPoint, dstPoint);
				break;
			}
			case 'b':
			{// a bishop
				r_val = move_bishop(srcPoint, dstPoint);
				break;
			}
			case 'n':
			{// a knight
				r_val = move_knight(srcPoint, dstPoint);
				break;
			}
			case 'q':
			{// a queen
				r_val = move_queen(srcPoint, dstPoint);
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else
	{
		this->curr_msg_to_graphics = '3'; // both figures dst and src are from the same player
		return false;
	}
	if (r_val)
	{
		this->set_board_str(); // update the board
		is_chess(dstPoint); // check if move makes or blocks chess
		
		std::string temp = "4";
		if (this->curr_msg_to_graphics.compare(temp) == 0)
		{// if move caused chess to the same player
			r_val = false;
			switch_positions(dstPoint, srcPoint); // return the figure to its old place
		}
	}

	return r_val;
}

bool board::move_pawn(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	Figure& curr = *this->board_figures[src_x + src_y * ROW];
	bool r_val = false;
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);
	char temp = 'a';

	//if there is a figure in the srcPoint
	if (this->board_figures[src_x + src_y * ROW] != nullptr)
	{
		if (this->board_str[dst_x + dst_y * ROW] != EMPTY)
		{// need to check if can eat what is in dstPoint
			if (curr.isWhite() && islower(this->board_str[dst_x + dst_y * ROW]))
			{//if white and dstPoint has black figure
				if ((curr.currPos_Y - dst_y == STEP) &&
					(dst_x - curr.currPos_X == STEP || curr.currPos_X - dst_x == STEP))
				{//if the pawn moves one step forword and left or right(1 step in diagonal)
					r_val = true;
				}
			}
			else if (!curr.isWhite() && !islower(this->board_str[dst_x + dst_y * ROW]))
			{// if black && eats white figure
				if ((dst_y - curr.currPos_Y == STEP) &&
					(dst_x - curr.currPos_X == STEP || curr.currPos_X - dst_x == STEP))
				{//if the pawn moves one step forword and left or right(1 step in diagonal)
					r_val = true;
				}
			}
			else
			{
				this->curr_msg_to_graphics = '3'; // dstPoint and srcPoint figures with the same color
				return false;
			}
			//move the piece if needed and delete the eatten piece
			if (r_val)
			{
				delete(this->board_figures[dst_x + dst_y * ROW]);
				this->board_str[dst_x + dst_y * ROW] = EMPTY;
			}
		}
		else if(curr.currPos_X == dst_x)
		{// need to check if pawn can move to empty place
			if ((curr.currPos_Y == START_LINE_BLACK || curr.currPos_Y == START_LINE_WHITE))
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
					if (curr.currPos_Y - dst_y == STEP)
					{//if the action is one step
						r_val = true;
					}
				}
				else
				{
					if (dst_y - curr.currPos_Y == STEP)
					{//if the action is one step
						r_val = true;
					}
				}
			}
		}
	}
	else
	{
		this->curr_msg_to_graphics = '2'; // srcPoint doesn't have a figure
		return false;
	}

	// set variables of pos to new point
	if (r_val)
	{
		this->curr_msg_to_graphics = '0'; // valid move was made

		// if pawn gets to the last line he turns into a queen.
		if (dst_y == ROW || dst_y == 0)
		{
			// place the queen by the pawn's color
			if (this->board_figures[src_x + src_y * ROW]->isWhite())
			{
				this->board_str[dst_x + dst_y * ROW] = 'Q'; // white queen
			}
			else
			{
				this->board_str[dst_x + dst_y * ROW] = 'q'; // black queen
			}

			// delete src point
			delete(this->board_figures[src_x + src_y * ROW]);
			this->board_figures[src_x + src_y * ROW] = nullptr;
			this->board_str[src_x + src_y * ROW] = EMPTY;

			// create new queen in dstPoint
			this->board_figures[dst_x + dst_y * ROW] = new Queen(std::string(1, this->board_str[dst_x + dst_y * ROW]), dstPoint, !islower(this->board_str[dst_x + dst_y * ROW]));

			return true;
		}

		//move the figure
		this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
		this->board_figures[src_x + src_y * ROW] = nullptr;

		// set new params
		this->board_figures[dst_x + dst_y * ROW]->setX(dst_x);
		this->board_figures[dst_x + dst_y * ROW]->setY(dst_y);
		this->board_figures[dst_x + dst_y * ROW]->set_pos(dstPoint);

		// change the string of the board
		temp = this->board_str[src_x + src_y * ROW];
		this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
		this->board_str[dst_x + dst_y * ROW] = temp;
	}
	else
	{
		this->curr_msg_to_graphics = '6'; // invalid move was made
	}

	return r_val;
}

bool board::move_king(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	Figure& curr = *this->board_figures[src_x + src_y * ROW];
	bool r_val = false;
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);
	int len = this->board_str.length() - UNIMPORTANT_CHARS;
	int i = 0;
	int j = 0;
	char temp = 'a';

	//run loop to check if new pos of king not being attacked
	
	// set kings place to new pos to check
	curr.setX(dst_x);
	curr.setY(dst_y);
	temp = this->board_str[src_x + src_y * ROW];
	this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
	this->board_str[dst_x + dst_y * ROW] = temp;

	for (j = 0; j < ROW; j++)
	{
		for (i = 0; i < ROW; i++)
		{
			// if not null and does attack
			if(	this->board_figures[i + j * ROW] != nullptr &&  // if not null
				this->board_figures[i + j * ROW]->isWhite() != this->board_figures[src_x + src_y * ROW]->isWhite() &&  // if not null
				this->board_figures[i + j * ROW] != this->board_figures[src_x + src_y * ROW] &&  // if not the same figure
				this->board_figures[i + j * ROW] != this->board_figures[dst_x + dst_y * ROW] &&  // if not the same figure
				this->board_figures[i + j * ROW]->does_attack(dstPoint)) // if figure attacks
			{
				this->curr_msg_to_graphics = '4'; // the move will couse the user to get chess
				return false;
			}
		}
	}

	// set kings place to old pos to check the rest of the conditions
	curr.setX(src_x);
	curr.setY(src_y);
	temp = this->board_str[src_x + src_y * ROW];
	this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
	this->board_str[dst_x + dst_y * ROW] = temp;

	if (this->board_str[dst_x + dst_y * ROW] != EMPTY)
	{// need to check if can eat what is in dstPoint
		if (curr.isWhite() && islower(this->board_str[dst_x + dst_y * ROW]) ||
			!curr.isWhite() && !islower(this->board_str[dst_x + dst_y * ROW]))
		{//if white and dstPoint has black figure or if black && eats white figure
			if (abs(dst_x - src_x) <= STEP && (abs(dst_y - src_y) <= STEP))
			{//if the king moves one step forword or backwards or left or right
				r_val = true;

				//delete the eaten piece
				delete(this->board_figures[dst_x + dst_y * ROW]);
				this->board_str[dst_x + dst_y * ROW] = EMPTY;
			}
		}
	}
	else
	{// need to check if king can move to empty place
		if (abs(dst_x - src_x) <= STEP && (abs(dst_y - src_y) <= STEP))
		{//if the king moves one step forword or backwards and left or right(1 step in diagonal)
			r_val = true;
		}
	}

	// set variables of pos to new point
	if (r_val)
	{
		this->curr_msg_to_graphics = '0'; // valid move

		//move the figure
		this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
		this->board_figures[src_x + src_y * ROW] = nullptr;

		this->board_figures[dst_x + dst_y * ROW]->setX(dst_x);
		this->board_figures[dst_x + dst_y * ROW]->setY(dst_y);
		this->board_figures[dst_x + dst_y * ROW]->set_pos(dstPoint);

		// change the string of the board
		temp = this->board_str[src_x + src_y * ROW];
		this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
		this->board_str[dst_x + dst_y * ROW] = temp;
	}
	else
	{
		this->curr_msg_to_graphics = '6'; // ivalid move was made
	}

	return r_val;
}

bool board::move_rook(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	Figure& curr = *this->board_figures[src_x + src_y * ROW];
	bool r_val = true;
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);
	char temp = 'a';
	int yIncrement = 0;
	int xIncrement = 0;
	int i = 0;

	if ((curr.currPos_X != dst_x) || (curr.currPos_Y != dst_y))
	{//if the rook moves in x or y
		if (curr.currPos_X == dst_x)
		{// check if no piece is in the middle in x row
			yIncrement = (dst_y - curr.currPos_Y) / (abs(dst_y - curr.currPos_Y));

			for (i = curr.currPos_Y + yIncrement; i != dst_y; i += yIncrement)
			{//check each square until the dstPoint
				if (this->board_str[curr.currPos_X + i*ROW] != EMPTY)
				{//found piece in the middle of the way
					return false;
					this->curr_msg_to_graphics = '6'; // ivalid move was made
				}

			}
		}
		else if (curr.currPos_Y == dst_y)
		{
			xIncrement = (dst_x - curr.currPos_X) / (abs(dst_x - curr.currPos_X));

			for (i = curr.currPos_X + xIncrement; i != dst_x; i += xIncrement)
			{//check each square until the dstPoint
				if (this->board_str[i + curr.currPos_Y * ROW] != EMPTY)
				{//found piece in the middle of the way
					return false;
					this->curr_msg_to_graphics = '6'; // ivalid move was made
				}

			}
		}
		else
		{
			this->curr_msg_to_graphics = '6'; // ivalid move was made
			r_val = false;
		}

		if (this->board_str[dst_x + dst_y * ROW] != EMPTY)
		{// need to check if can eat what is in dstPoint
			if (curr.isWhite() && islower(this->board_str[dst_x + dst_y * ROW]) ||
				(!curr.isWhite() && !islower(this->board_str[dst_x + dst_y * ROW])))
			{//if white and dstPoint has black figure or the opposite
		//move the piece and delete the eatten piece
				delete(this->board_figures[dst_x + dst_y * ROW]);
				this->board_str[dst_x + dst_y * ROW] = EMPTY;
			}
			else
			{
				this->curr_msg_to_graphics = '3'; // src and dst figures are with the same color
				r_val = false;
			}
		}
	}
	else
	{
		this->curr_msg_to_graphics = '6'; // ivalid move was made
		return false;
	}

	// set variables of pos to new point
	if (r_val)
	{
		this->curr_msg_to_graphics = '0'; // valid move was made
		//move the figure
		this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
		this->board_figures[src_x + src_y * ROW] = nullptr;

		this->board_figures[dst_x + dst_y * ROW]->setX(dst_x);
		this->board_figures[dst_x + dst_y * ROW]->setY(dst_y);
		this->board_figures[dst_x + dst_y * ROW]->set_pos(dstPoint);

		// change the string of the board
		temp = this->board_str[src_x + src_y * ROW];
		this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
		this->board_str[dst_x + dst_y * ROW] = temp;
	}

	return r_val;
}

bool board::move_bishop(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	Figure& curr = *this->board_figures[src_x + src_y * ROW];
	bool r_val = true;
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);
	char temp = 'a';

	if (abs(curr.currPos_X - dst_x) == abs(curr.currPos_Y - dst_y))
	{
		//checkk all points in diaganale until dstPoint
		int xIncrement = (dst_x - curr.currPos_X) / (abs(dst_x - curr.currPos_X));
		int yIncrement = (dst_y - curr.currPos_Y) / (abs(dst_y - curr.currPos_Y));

		for (int i = 1; i < abs(curr.currPos_X - dst_x); i++)
		{
			if (this->board_str[(curr.currPos_X + xIncrement * i) + (curr.currPos_Y + yIncrement * i) * ROW] != EMPTY)
			{
				this->curr_msg_to_graphics = '6'; // ivalid move was made
				r_val = false;
				return r_val; // stop loop
			}
		}

		if (curr.isWhite() && islower(this->board_str[dst_x + dst_y * ROW]) ||
			(!curr.isWhite() && !islower(this->board_str[dst_x + dst_y * ROW])))
		{//if white and dstPoint has black figure or the opposite
			//delete the eatten piece
			delete(this->board_figures[dst_x + dst_y * ROW]);
			this->board_str[dst_x + dst_y * ROW] = EMPTY;
		}
		else
		{
			this->curr_msg_to_graphics = '3'; // both figures dst and src are from the same player
		}

	}
	else
	{
		this->curr_msg_to_graphics = '6'; // ivalid move was made
		r_val = false;
	}

	if (r_val)
	{
		this->curr_msg_to_graphics = '0'; // valid move was made
		//move the figure
		this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
		this->board_figures[src_x + src_y * ROW] = nullptr;

		this->board_figures[dst_x + dst_y * ROW]->setX(dst_x);
		this->board_figures[dst_x + dst_y * ROW]->setY(dst_y);
		this->board_figures[dst_x + dst_y * ROW]->set_pos(dstPoint);

		// change the string of the board
		temp = this->board_str[src_x + src_y * ROW];
		this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
		this->board_str[dst_x + dst_y * ROW] = temp;
	}
	return r_val;
}

bool board::move_knight(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	Figure& curr = *this->board_figures[src_x + src_y * ROW];
	bool r_val = true;
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);
	char temp = 'a';

	if ((abs(src_x - dst_x) == TWO_STEPS && abs(src_y - dst_y) == STEP) || (abs(src_x - dst_x) == STEP && abs(src_y - dst_y) == TWO_STEPS))
	{
		if (this->board_str[dst_x + dst_y * ROW] != EMPTY)
		{
			if (curr.isWhite() && islower(this->board_str[dst_x + dst_y * ROW]) ||
				(!curr.isWhite() && !islower(this->board_str[dst_x + dst_y * ROW])))
			{//if white and dstPoint has black figure or the opposite
				//delete the eatten piece
				delete(this->board_figures[dst_x + dst_y * ROW]);
				this->board_str[dst_x + dst_y * ROW] = EMPTY;
			}
			else
			{
				this->curr_msg_to_graphics = '3'; // both figures dst and src are from the same player
				return false;
			}
		}

		this->curr_msg_to_graphics = '0'; // valid move was made

		//move the figure
		this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
		this->board_figures[src_x + src_y * ROW] = nullptr;

		this->board_figures[dst_x + dst_y * ROW]->setX(dst_x);
		this->board_figures[dst_x + dst_y * ROW]->setY(dst_y);
		this->board_figures[dst_x + dst_y * ROW]->set_pos(dstPoint);

		// change the string of the board
		temp = this->board_str[src_x + src_y * ROW];
		this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
		this->board_str[dst_x + dst_y * ROW] = temp;

		r_val = true;
	}
	else
	{
		this->curr_msg_to_graphics = '6'; // ivalid move was made
		r_val = false;
	}

	return r_val;
}

bool board::move_queen(std::string srcPoint, std::string dstPoint)
{
	int src_x = Figure::get_tran_x(srcPoint);
	int src_y = Figure::get_tran_y(srcPoint);
	Figure& curr = *this->board_figures[src_x + src_y * ROW];
	bool r_val = false;
	int dst_x = Figure::get_tran_x(dstPoint);
	int dst_y = Figure::get_tran_y(dstPoint);
	char temp = 'a';
	int yIncrement = 0;
	int xIncrement = 0;

	if (src_x != dst_x || src_y != dst_y)
	{

		if (src_x == dst_x)
		{
			yIncrement = (dst_y - src_y) / (abs(dst_y - src_y));
			for (int i = src_y + yIncrement; i != dst_y; i += yIncrement)
			{

				if (this->board_str[dst_x + i * ROW] != EMPTY)
				{
					this->curr_msg_to_graphics = '6'; // ivalid move was made
					return false;
				}
			}
		}
		else
			if (src_y == dst_y)
			{

				xIncrement = (dst_x - src_x) / (abs(dst_x - src_x));
				for (int i = src_x + xIncrement; i != dst_x; i += xIncrement)
				{
					if (this->board_str[i + dst_y * ROW] != EMPTY)
					{
						this->curr_msg_to_graphics = '6'; // ivalid move was made
						return false;
					}
				}
			}
			else
				if (abs(src_x - dst_x) == abs(src_y - dst_y))
				{
					xIncrement = (dst_x - src_x) / (abs(dst_x - src_x));
					yIncrement = (dst_y - src_y) / (abs(dst_y - src_y));

					for (int i = 1; i < abs(src_x - dst_x); i++)
					{
						if (this->board_str[src_x + xIncrement * i + (src_y + yIncrement * i) * ROW] != EMPTY)
						{
							this->curr_msg_to_graphics = '6'; // ivalid move was made
							return false;
						}
					}
				}
				else
				{
					this->curr_msg_to_graphics = '6'; // ivalid move was made
					return false;
				}
	}



	// set variables of pos to new point
	if (!r_val)
	{
		if (this->board_str[dst_x + dst_y * ROW] != EMPTY)
		{
			if (curr.isWhite() && islower(this->board_str[dst_x + dst_y * ROW]) ||
				(!curr.isWhite() && !islower(this->board_str[dst_x + dst_y * ROW])))
			{//if white and dstPoint has black figure or the opposite
				//delete the eatten piece
				delete(this->board_figures[dst_x + dst_y * ROW]);
				this->board_str[dst_x + dst_y * ROW] = EMPTY;
			}
			else
			{
				this->curr_msg_to_graphics = '3'; // both figures dst and src are from the same player
				return false;
			}
		}

		this->curr_msg_to_graphics = '0'; // valid move was made

		//move the figure
		this->board_figures[dst_x + dst_y * ROW] = this->board_figures[src_x + src_y * ROW];
		this->board_figures[src_x + src_y * ROW] = nullptr;

		//set new coordinates
		this->board_figures[dst_x + dst_y * ROW]->setX(dst_x);
		this->board_figures[dst_x + dst_y * ROW]->setY(dst_y);
		this->board_figures[dst_x + dst_y * ROW]->set_pos(dstPoint);

		// change the string of the board
		temp = this->board_str[src_x + src_y * ROW];
		this->board_str[src_x + src_y * ROW] = this->board_str[dst_x + dst_y * ROW];
		this->board_str[dst_x + dst_y * ROW] = temp;
	}
}
