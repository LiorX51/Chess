#include "Bishop.h"

Bishop::Bishop(std::string name, std::string start_pos, bool is_white) : Figure(name, start_pos, is_white)
{

}

bool Bishop::does_attack(std::string Point)
{
	bool r_val = false;
	int dst_x = get_tran_x(Point);
	int dst_y = get_tran_y(Point);

	if (abs(this->currPos_X - dst_x) == abs(this->currPos_Y - dst_y))
	{
		r_val = true;
	}
	return r_val;
}
