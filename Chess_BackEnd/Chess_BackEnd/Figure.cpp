#include "Figure.h"

Figure::Figure(const std::string name, const std::string start_pos, const bool is_white)
{
    this->name = name;
    set_pos(start_pos);
    setWhite(is_white);

    tran_strPos_to_X_Y();
}

Figure::~Figure()
{
}

bool Figure::isWhite()
{
    return this->is_white;
}

void Figure::setWhite(const bool isWhite)
{
    this->is_white = isWhite;
}

std::string Figure::getName()
{
    return this->name;
}

void Figure::set_pos(const std::string pos)
{
    this->currPos = pos;
}

void Figure::tran_strPos_to_X_Y()
{
    this->currPos_X = this->currPos[0] - 'a'; // 'b' - 'a' = 1
    this->currPos_Y = '8' - this->currPos[1]; // '8' - '8' = 0
}

void Figure::setX(const int x)
{
    this->currPos_X = x;
}

void Figure::setY(const int y)
{
    this->currPos_Y = y;
}

int Figure::get_tran_x(const std::string dst_pos)
{
    return dst_pos[0] - 'a';
}

int Figure::get_tran_y(const std::string dst_pos)
{
    return '8' - dst_pos[1];
}