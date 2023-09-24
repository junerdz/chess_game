#include <SFML/Graphics.hpp>
#include "chess_window.hpp"
using namespace sf;

const String pieces_pics[12] = {"images/512h/b_bishop_png_512px.png",
                                    "images/512h/b_king_png_512px.png",
                                    "images/512h/b_knight_png_512px.png",
                                    "images/512h/b_pawn_png_512px.png",
                                    "images/512h/b_queen_png_512px.png",
                                    "images/512h/b_rook_png_512px.png",
                                    "images/512h/w_bishop_png_512px.png",
                                    "images/512h/w_king_png_512px.png",
                                    "images/512h/w_knight_png_512px.png",
                                    "images/512h/w_pawn_png_512px.png",
                                    "images/512h/w_queen_png_512px.png",
                                    "images/512h/w_rook_png_512px.png"};


int main(){
    ChessWindow window(640, 640, "Chess", pieces_pics);
    while(window.update())
    {
    }
    return 0;

}