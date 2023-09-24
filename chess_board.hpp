#include <SFML/Graphics.hpp>
using namespace sf;

// Game Board (put into a struct so we can manipulate it)
struct Board{
    // White is represented by 0
    // Black is represented by 1
    bool turn = 0;

  // Black (0-5) 
  // White (6-11)
    int board[8][8] = 
  {{ 5,  2,  0,  4,  1,  0,  2,  5},
   { 3,  3,  3,  3,  3,  3,  3,  3},
   {-1, -1, -1, -1, -1, -1, -1, -1},
   {-1, -1, -1, -1, -1, -1, -1, -1},
   {-1, -1, -1, -1, -1, -1, -1, -1},
   {-1, -1, -1, -1, -1, -1, -1, -1},
   { 9,  9,  9,  9,  9,  9,  9,  9},
   {11,  8,  6, 10,  7,  6,  8, 11}};
 
};

