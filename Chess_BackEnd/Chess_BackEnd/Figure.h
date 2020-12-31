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

	Figure(const std::string name, const std::string start_pos, const bool is_white);
	~Figure();
	bool isWhite();
	void setWhite(const bool isWhite);
	std::string getName();
	void set_pos(const std::string pos);
	void tran_strPos_to_X_Y();
	void setX(const int x);
	void setY(const int y);
	static int get_tran_x(const std::string dst_pos);
	static int get_tran_y(const std::string dst_pos);
	virtual bool does_attack(const std::string Point) = 0;
private:
	
};

#endif
