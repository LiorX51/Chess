#pragma once

#include <string>
#include <iostream>
#include "Figure.h"
#include "pawn.h"
#define EMPTY '#'

class board 
{
	public:
		std::string board_str;
		Figure * board_figures[64];

		board();
		~board();
		std::string get_board();
		void set_board_figures();
};

