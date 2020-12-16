#ifndef FIGURE_H
#define FIGURE_H

#include "board.h"

class Figure : public board
{

public:

	std::string name;
	int currPos_Y;
	int currPos_X;
	std::string currPos;
	bool is_white;

	Figure(std::string name, std::string start_pos, bool is_white);
	~Figure();
	bool isWhite();
	void setWhite(bool isWhite);
	std::string getName();
	void set_pos(std::string pos);
	void tran_strPos_to_X_Y();
	void setX(int x);
	void setY(int y);
	int get_tran_x(std::string dst_pos);
	int get_tran_y(std::string dst_pos);
	virtual bool can_move(std::string dstPoint) = 0;
private:
	
};

#endif
