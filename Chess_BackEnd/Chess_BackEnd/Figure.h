#ifndef FIGURE_H
#define FIGURE_H
#include <string>
#include <iostream>

class Figure
{
	std::string name;
	int currPos_Y;
	int currPos_X;
	std::string currPos;
	bool is_white;

public:
	bool isWhite();
	void setWhite(bool isWhite);
	std::string getName();
	void set_pos(std::string pos);
	void tran_strPos_to_X_Y();
	void setX(int x);
	void setY(int y);
	virtual bool can_move(std::string dstPoint) = 0;
private:
	
};

#endif
