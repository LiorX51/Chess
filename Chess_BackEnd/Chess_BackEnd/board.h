#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include "Figure.h"
#include "pawn.h"
#define EMPTY '#'
#define ROW   8

class board 
{
	public:
		std::string board_str;
		Figure* board_figures[64];

		board();
		~board();
		std::string get_board();
		void set_board_figures();


		bool move_pawn(std::string srcPoint, std::string dstPoint);
};

#endif // !BOARD_H
