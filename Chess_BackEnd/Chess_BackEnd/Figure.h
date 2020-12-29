#ifndef FIGURE_H
#define FIGURE_H

#include <string>
#include <iostream>

#define ROW 8
#define EMPTY '#'

class Figure
{

public:

	std::string board_str;
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
	static int get_tran_x(std::string dst_pos);
	static int get_tran_y(std::string dst_pos);
	virtual bool does_attack(std::string Point) = 0;
private:
	
};

#endif
