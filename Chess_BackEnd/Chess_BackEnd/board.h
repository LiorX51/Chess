#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include "Figure.h"

#include "pawn.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"

#define BLACK_KING 'k'
#define WHITE_KING 'K'
#define EMPTY '#'
#define ROW   8
#define UNIMPORTANT_CHARS 2

class board 
{
	public:
		std::string board_str;
		Figure* board_figures[ROW*ROW];
		std::string curr_msg_to_graphics;
		bool is_turn_white;

		board();
		~board();
		void switch_positions(const std::string srcPoint, const std::string dstPoint);
		std::string get_board();
		void set_board_figures();
		void set_board_str();

		bool is_chess(const std::string figure_pos);

		bool move_figure(const std::string srcPoint, const std::string dstPoint);

	private:
		bool move_pawn(const std::string srcPoint, const std::string dstPoint);
		bool move_king(const std::string srcPoint, const std::string dstPoint);
		bool move_rook(const std::string srcPoint, const std::string dstPoint);
		bool move_bishop(const std::string srcPoint, const std::string dstPoint);
		bool move_knight(const std::string srcPoint, const std::string dstPoint);
		bool move_queen(const std::string srcPoint, const std::string dstPoint);
};

#endif // !BOARD_H
