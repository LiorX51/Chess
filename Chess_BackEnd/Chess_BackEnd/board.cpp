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
	delete(board_figures);
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

	for (i = 0; (i + j*8) < len; i++)
	{
		for (j = 0; j < 8; j++)
		{
			pos = ('a' + i) + (char)8 - j;

			switch (this->board_str[i + j*8])
			{
			case 'p':
			{
				// create a new pawn and place it in the write place;
				this->board_figures[i + j * 8] = new Pawn("p", pos, islower(this->board_str[i + j * 8]));;
				break;
			}
			default:
				break;
			}
		}
	}
}
