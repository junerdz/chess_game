#include <SFML/Graphics.hpp>
// #include "chess_board.hpp"
using namespace sf;

struct Piece
{
    Sprite sprite;
    int type, pos_x, pos_y;
    int alive = 0;
};


