#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "chess_board.hpp"
#include "chess_piece.hpp"
using namespace sf;


class ChessWindow{
    private:
        RenderWindow window;
        RectangleShape tiles[8][8];
        Color tile_colors[2];
        int height, width;

        // represents EVERY tile on the board (and what Piece is on it, if there is one)
        Piece pieces[64];

        Texture piece_textures[12];

        // represents the current Game Board
        Board chess_board;
  
        int tile_coords[2];
        bool highlight = 0;

        // type of piece stored in tile_coords[2]
        int piece_type;

        void set_tiles();
        void draw_tiles();
        void set_pieces();
        void set_pieces(int old_x, int old_y, int new_x, int new_y);
        void draw_pieces();
        void load_textures(const String images[12]);
        bool is_valid_piece_selection( int mouse_pos_x, int mouse_pos_y, bool turn);
        bool is_valid_kill( int old_x, int old_y, int mouse_pos_x, int mouse_pos_y, bool turn);
        void next_turn();

        // ALL Chess Piece Functions
        bool white_pawn(int old_x, int old_y, int new_x, int new_y);
        bool black_pawn(int old_x, int old_y, int new_x, int new_y);
        bool knight(int old_x, int old_y, int new_x, int new_y, bool turn);
        bool king(int old_x, int old_y, int new_x, int new_y, bool turn);
        bool rook(int old_x, int old_y, int new_x, int new_y, bool turn);
        bool bishop(int old_x, int old_y, int new_x, int new_y, bool turn);
        bool queen(int old_x, int old_y, int new_x, int new_y, bool turn);

    public:
        ChessWindow(int height, int width, String name, const String images[12]);
        bool update();
};


