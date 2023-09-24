#include "chess_window.hpp"



/*
Sets Tile Position and Size
*/
void ChessWindow::set_tiles()
{
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            tiles[i][j].setSize(Vector2f(80.f,80.f));
            tiles[i][j].setPosition(j*80, i*80);


        }
    }
}

/*
Draws Tiles to the RenderWindow
*/
void ChessWindow::draw_tiles()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            window.draw(tiles[i][j]);
        }
    }
}

/*
Set Default Piece Position and Size
*/
void ChessWindow::set_pieces()
{
    for(int i = 0; i < 64; i++)
    {
        if(pieces[i].alive == 1)
        {
            pieces[i].sprite.setPosition((pieces[i].pos_x*80) + 8.25, (pieces[i].pos_y*80) + 8);
            pieces[i].sprite.setScale((1.0/8.0), (1.0/8.0));
        }
    }
}

/*
Set Piece Position, Size, and Texture
*/
void ChessWindow::set_pieces(int old_x, int old_y, int new_x, int new_y)
{
    Piece* curr;
    for( int i = 0; i < 64; i++)
    {
        if(pieces[i].alive == 1)
        {
            if( pieces[i].pos_x == old_x && pieces[i].pos_y == old_y)
            {
                curr = &pieces[i];
            }
            if( pieces[i].pos_x == new_x && pieces[i].pos_y == new_y)
            {
                pieces[i].alive = 0;
            }
            pieces[i].sprite.setPosition((pieces[i].pos_x*80) + 8.25, (pieces[i].pos_y*80) + 8);
            pieces[i].sprite.setScale((1.0/8.0), (1.0/8.0));
        }
    }
    curr->pos_x = new_x;
    curr->pos_y = new_y;
    curr->sprite.setPosition((curr->pos_x*80) + 8.25, (curr->pos_y*80) + 8);
    curr->sprite.setScale((1.0/8.0), (1.0/8.0));

}

/*
Using the window.draw() Function, draws the Pieces that are alive to the Window
*/
void ChessWindow::draw_pieces()
{
    for(int i = 0; i < 64; i++)
    {
        if(pieces[i].alive == 1)
        {
            window.draw(pieces[i].sprite);
        }
    }
}

/*
Load Piece Textures from File
*/
void ChessWindow::load_textures(const String images[12])
{
    for(int i = 0; i < 12; i++)
    {
        piece_textures[i].loadFromFile(images[i]);
    }
}

/*
Checks if what Piece the Mouse has selected is valid
*/
bool ChessWindow::is_valid_piece_selection( int mouse_pos_x, int mouse_pos_y, bool turn)
{
    // loop thru pieces[64]
    // 1 for turn means Black (0 - 5)
    for(int i = 0; i < 64; i++)
    {
        // 0 for turn means White (6 - 11 for type)
        if(turn == 0)
        {
            if(pieces[i].pos_x == mouse_pos_y && pieces[i].pos_y == mouse_pos_x && pieces[i].alive != 0
            && pieces[i].type >= 6 && pieces[i].type <= 11)
            {
                piece_type = pieces[i].type;
                return 1;
            }
        }
        if(turn == 1)
        {
            if(pieces[i].pos_x == mouse_pos_y && pieces[i].pos_y == mouse_pos_x && pieces[i].alive != 0
            && pieces[i].type >= 0 && pieces[i].type <= 5)
            {
                piece_type = pieces[i].type;
                return 1;
            }
        }
    }
    // returns False if the selected Piece is NOT valid
    return 0;
}

/*
Checks if what Piece the Mouse has selected is valid
*/
bool ChessWindow::is_valid_kill( int old_x, int old_y, int mouse_pos_x, int mouse_pos_y, bool turn)
{
    // Call Function for White Pawn
    if( chess_board.board[old_x][old_y] == 9 )
    {
        return white_pawn(old_x, old_y, mouse_pos_x, mouse_pos_y);
    }
    // Call Function for Black Pawn
    if( chess_board.board[old_x][old_y] == 3 )
    {
        return black_pawn(old_x, old_y, mouse_pos_x, mouse_pos_y);
    }
    // Call Function for Knight
    if( chess_board.board[old_x][old_y] == 2 ||  chess_board.board[old_x][old_y] == 8)
    {
        return knight(old_x, old_y, mouse_pos_x, mouse_pos_y, turn);
    }
    // Call Function for King
    if( chess_board.board[old_x][old_y] == 1 ||  chess_board.board[old_x][old_y] == 7)
    {
        return king(old_x, old_y, mouse_pos_x, mouse_pos_y, turn);
    }
    // Call Function for Rook
    if( chess_board.board[old_x][old_y] == 5 ||  chess_board.board[old_x][old_y] == 11)
    {
        return rook(old_x, old_y, mouse_pos_x, mouse_pos_y, turn);
    }
    // Call Function for Bishop
    if( chess_board.board[old_x][old_y] == 0 ||  chess_board.board[old_x][old_y] == 6)
    {
        return bishop(old_x, old_y, mouse_pos_x, mouse_pos_y, turn);
    }
    // Call Function for Queen
    if( chess_board.board[old_x][old_y] == 4 ||  chess_board.board[old_x][old_y] == 10)
    {
        return queen(old_x, old_y, mouse_pos_x, mouse_pos_y, turn);
    }

    return 0;
}




/*
Construtor for ChessWindow
*/
ChessWindow::ChessWindow(int height, int width, String name, const String images[12])
{
    // Set tile colors
    tile_colors[0] = Color(245, 245, 220);
    tile_colors[1] = Color(150,75,0);

    // Add color to tiles
    bool tile_color = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

            tiles[i][j].setFillColor(tile_colors[tile_color]);

            tile_color = !tile_color;
        }
        tile_color = !tile_color;
    }
    set_tiles();

    load_textures(images);

    // After textures have been loaded, set the Texture and other attributes to the Pieces 
    int counter = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            pieces[counter].type = chess_board.board[i][j];
            pieces[counter].pos_x = j;
            pieces[counter].pos_y = i;


            if(pieces[counter].type != -1)
            {
                pieces[counter].sprite.setTexture(piece_textures[pieces[counter].type], true);
                pieces[counter].alive = 1;

            }
            counter++;
        }
    }
    // Set the Pieces onto their default locations on the board
    set_pieces();



    window.create(VideoMode(height, width), name);
}

/*
Updates the Pieces on the ChessWindow
*/
bool ChessWindow::update()
{
    Event event;
    while(window.pollEvent(event)){

        switch( event.type )
        { 
        case Event::Closed:
            window.close();
            return 0;
        
        case Event::MouseButtonPressed:
            /*
            Uses tile_coords[2] to store the coordinates of the Right Mouse Click
            to then be used to compare it to the current Mouse click
            

            */
            int mouse_pos_x = (event.mouseButton.y/80);
            int mouse_pos_y = (event.mouseButton.x/80);

            if(event.mouseButton.button == Mouse::Button::Left)
            {
                if( highlight == 0 )
                {
                    if(is_valid_piece_selection(mouse_pos_x, mouse_pos_y, chess_board.turn)){
                        tile_coords[0] = mouse_pos_x;
                        tile_coords[1] = mouse_pos_y;
                        tiles[mouse_pos_x][mouse_pos_y].setFillColor(Color(168, 202, 68));
                        highlight = 1;
                        std::cout << piece_type  << std::endl;
                    }
                }
                else
                {
                    if(tile_coords[0] == mouse_pos_x && tile_coords[1] == mouse_pos_y)
                    {
                        tiles[mouse_pos_x][mouse_pos_y].setFillColor(tile_colors[((tile_coords[0] + tile_coords[1]) % 2) ]);
                        highlight = 0;
                    }
                    else
                    {
                        if(is_valid_kill( tile_coords[0], tile_coords[1], mouse_pos_x, mouse_pos_y, chess_board.turn))
                        {
                            std::cout << "Position of New Tile: " << std::endl;
                            std::cout << mouse_pos_x << std::endl;
                            std::cout << mouse_pos_y << std::endl;

                            std::cout << "Position of Old Tile: " << std::endl;
                            std::cout << tile_coords[0] << std::endl;
                            std::cout << tile_coords[1]  << std::endl;

                            

                            chess_board.board[mouse_pos_x][mouse_pos_y] = chess_board.board[tile_coords[0]][tile_coords[1]];
                            chess_board.board[tile_coords[0]][tile_coords[1]] = -1;
                            tiles[tile_coords[0]][tile_coords[1]].setFillColor(tile_colors[((tile_coords[0] + tile_coords[1]) % 2) ]);
                            highlight = 0;
                            set_pieces(tile_coords[1], tile_coords[0], mouse_pos_y, mouse_pos_x);

                        
                        next_turn();
                        }                        

                    }  
                 
                }
            }

        }

    }
    window.clear();
    draw_tiles();
    draw_pieces();
    window.display();
    return 1;
}

/*
Function for changing turns after move has been made
*/
void ChessWindow::next_turn()
{
    chess_board.turn = !chess_board.turn;
}

/*
Checks if Mouse clicked on a valid Tile for White Pawn
*/
bool ChessWindow::white_pawn(int old_x, int old_y, int new_x, int new_y)
{
    if( old_x > 0 )
    {
        if(chess_board.board[old_x - 1][old_y] == -1 )
        {
            if( old_x == 6 && (chess_board.board[old_x - 2][old_y] == -1) 
            && new_x == (old_x - 2) && new_y == old_y)
            {
                return 1;
            }
            if(new_x == (old_x - 1) && new_y == old_y)
            {
                return 1;
            }
        }
        // Checks Upper Left Tile to see if Black Piece can be eaten
        if( old_y > 0)
        {
            if( (chess_board.board[old_x - 1][old_y - 1] < 6 && chess_board.board[old_x - 1][old_y - 1] >= 0 ) 
            && new_x == (old_x - 1) && new_y == (old_y - 1))
            {
                return 1;
            }
        }
        // Checks Upper Right Tile to see if White Piece can be eaten
        if( old_y < 7)
        {
            if( (chess_board.board[old_x - 1][old_y + 1] < 6 && chess_board.board[old_x - 1][old_y + 1] >= 0 ) 
            && new_x == (old_x - 1) && new_y == (old_y + 1))
            {
                return 1;
            }
        }

    }
    return 0;
}

/*
Checks if Mouse clicked on a valid Tile for Black Pawn
*/
bool ChessWindow::black_pawn(int old_x, int old_y, int new_x, int new_y)
{
    if( old_x < 7 )
    {
        if(chess_board.board[old_x + 1][old_y] == -1 )
        {
            if( old_x == 1 && (chess_board.board[old_x + 2][old_y] == -1) 
            && new_x == (old_x + 2) && new_y == old_y)
            {
                return 1;
            }
            if(new_x == (old_x + 1) && new_y == old_y)
            {
                return 1;
            }
        }
        // Check if Bottom Left Tile has White Piece that can be eaten
        if(old_y > 0)
        {
            if( (chess_board.board[old_x + 1][old_y - 1] <= 11 && chess_board.board[old_x + 1][old_y - 1] >= 6 ) 
            && new_x == (old_x + 1) && new_y == (old_y - 1))
            {
                return 1;
            }
        }
        // Check if Bottom Left Tile has White Piece that can be eaten
        if(old_y < 7)
        {
            if( (chess_board.board[old_x + 1][old_y + 1] <= 11 && chess_board.board[old_x + 1][old_y + 1] >= 6 ) 
            && new_x == (old_x + 1) && new_y == (old_y + 1))
            {
                return 1;
            }
        }
        

    }
    return 0;
}

/*
Checks if Mouse clicked on a valid Tile for Knight
*/
bool ChessWindow::knight(int old_x, int old_y, int new_x, int new_y, bool turn)
{
    int min, max;
    if( turn == 0 )
    {
        // If it's White's Turn, then insert Black's Piece range
        min = 0;
        max = 5;
    }
    else if( turn == 1)
    {
        // If it's Black's Turn, then insert White's Piece range
        min = 6;
        max = 11;
    }

    // Check to see if Bottom L's Left move can be made
    if( old_x < 6 && old_y > 0)
    {
        if(((chess_board.board[old_x + 2][old_y - 1] == -1)
        || ((chess_board.board[old_x + 2][old_y - 1] >= min ) && (chess_board.board[old_x + 2][old_y - 1] <= max)))
        && new_x == (old_x + 2) && new_y == (old_y - 1))
        {
            return 1;
        }
    }
    // Check to see if Bottom L's Right move can be made
    if( old_x < 6 && old_y < 7 )
    {
        if(((chess_board.board[old_x + 2][old_y + 1] == -1)
        || ((chess_board.board[old_x + 2][old_y + 1] >= min) && (chess_board.board[old_x + 2][old_y + 1] <= max)))
        && new_x == (old_x + 2) && new_y == (old_y + 1))
        {
            return 1;
        }
    }
    // Check to see if Left L's Top move can be made 
    if( old_x > 0 && old_y > 1 )
    {
        if(((chess_board.board[old_x - 1][old_y - 2] == -1)
        || ((chess_board.board[old_x - 1][old_y - 2] >= min ) && (chess_board.board[old_x - 1][old_y - 2] <= max )))
        && new_x == (old_x - 1) && new_y == (old_y - 2))
        {
            return 1;
        }
    }
    // Check if Left L's Bottom move can be made
    if( old_x < 7 && old_y > 1 )
    {
        if(((chess_board.board[old_x + 1][old_y - 2] == -1)
        || ((chess_board.board[old_x + 1][old_y - 2] >= min ) && (chess_board.board[old_x + 1][old_y - 2] <= max )))
        && new_x == (old_x + 1) && new_y == (old_y - 2))
        {
            return 1;
        }
    }
    // Check if Top L's Left move can be made
    if( old_x > 1 && old_y > 0 )
    {
        if(((chess_board.board[old_x - 2][old_y - 1] == -1)
        || ((chess_board.board[old_x - 2][old_y - 1] >= min ) && (chess_board.board[old_x - 2][old_y - 1] <= max )))
        && new_x == (old_x - 2) && new_y == (old_y - 1))
        {
            return 1;
        }
    }
    // Check if Top L's Right move can be made
    if( old_x > 1 && old_y < 7 )
    {
        if(((chess_board.board[old_x - 2][old_y + 1] == -1)
        || ((chess_board.board[old_x - 2][old_y + 1] >= min ) && (chess_board.board[old_x - 2][old_y + 1] <= max )))
        && new_x == (old_x - 2) && new_y == (old_y + 1))
        {
            return 1;
        }
    }
    // Check if Right L's Top move can be made
    if( old_x > 0 && old_y < 6 )
    {
        if(((chess_board.board[old_x - 1][old_y + 2] == -1)
        || ((chess_board.board[old_x - 1][old_y + 2] >= min ) && (chess_board.board[old_x - 1][old_y + 2] <= max )))
        && new_x == (old_x - 1) && new_y == (old_y + 2))
        {
            return 1;
        }
    }
    // Check if Right L's Bottom move can be made
    if( old_x < 7 && old_y < 6 )
    {
        if(((chess_board.board[old_x + 1][old_y + 2] == -1)
        || ((chess_board.board[old_x + 1][old_y + 2] >= min ) && (chess_board.board[old_x + 1][old_y + 2] <= max )))
        && new_x == (old_x + 1) && new_y == (old_y + 2))
        {
            return 1;
        }
    }
    return 0;
}

/*
Checks if Mouse clicked on a valid Tile for King
*/
bool ChessWindow::king(int old_x, int old_y, int new_x, int new_y, bool turn)
{
    int min, max;
    if( turn == 0 )
    {
        // If it's White's Turn, then insert Black's Piece range
        min = 0;
        max = 5;
    }
    else if( turn == 1)
    {
        // If it's Black's Turn, then insert White's Piece range
        min = 6;
        max = 11;
    }


    // Northwest Tile
    if( old_x > 0 && old_y > 0)
    {
        if(((chess_board.board[old_x - 1][old_y - 1] == -1)
        || ((chess_board.board[old_x - 1][old_y - 1] >= min) && (chess_board.board[old_x - 1][old_y - 1] <= max)))
        && new_x == (old_x - 1) && new_y == (old_y - 1))
        {
            return 1;
        }
    }
    // North Tile
    if( old_x > 0)
    {
        if(((chess_board.board[old_x - 1][old_y] == -1)
        || ((chess_board.board[old_x - 1][old_y] >= min ) && (chess_board.board[old_x - 1][old_y] <= max )))
        && new_x == (old_x - 1) && (new_y == old_y))
        {
            return 1;
        }
    }
    // Northeast Tile
    if( old_x > 0 && old_y < 7 )
    {
        if(((chess_board.board[old_x - 1][old_y + 1] == -1)
        || ((chess_board.board[old_x - 1][old_y + 1] >= min ) && (chess_board.board[old_x - 1][old_y + 1] <= max )))
        && new_x == (old_x - 1) && new_y == (old_y + 1))
        {
            return 1;
        }
    }
    // West Tile
    if( old_y > 0 )
    {
        if(((chess_board.board[old_x][old_y - 1] == -1)
        || ((chess_board.board[old_x][old_y - 1] >= min ) && (chess_board.board[old_x][old_y - 1] <= max )))
        && new_x == (old_x) && new_y == (old_y - 1))
        {
            return 1;
        }
    }
    // East Tile
    if( old_y < 7 )
    {
        if(((chess_board.board[old_x][old_y + 1] == -1)
        || ((chess_board.board[old_x][old_y + 1] >= min ) && (chess_board.board[old_x][old_y + 1] <= max )))
        && new_x == (old_x) && new_y == (old_y + 1))
        {
            return 1;
        }
    }
    // Southwest Tile
    if( old_x < 7 && old_y > 0 )
    {
        if(((chess_board.board[old_x + 1][old_y - 1] == -1)
        || ((chess_board.board[old_x + 1][old_y - 1] >= min ) && (chess_board.board[old_x + 1][old_y - 1] <= max)))
        && new_x == (old_x + 1) && new_y == (old_y - 1))
        {
            return 1;
        }
    }
    // South Tile
    if( old_x < 7 )
    {
        if(((chess_board.board[old_x + 1][old_y] == -1)
        || ((chess_board.board[old_x + 1][old_y] >= min ) && (chess_board.board[old_x + 1][old_y] <= max )))
        && new_x == (old_x + 1) && new_y == old_y)
        {
            return 1;
        }
    }
    // Southeast Tile 
    if( old_x < 7 && old_y < 7 )
    {
        if(((chess_board.board[old_x + 1][old_y + 1] == -1)
        || ((chess_board.board[old_x + 1][old_y + 1] >= min ) && (chess_board.board[old_x + 1][old_y + 1] <= max )))
        && new_x == (old_x + 1) && new_y == (old_y + 1))
        {
            return 1;
        }
    }


    return 0;
}


/*
Checks if Mouse clicked on a valid Tile for King
*/
bool ChessWindow::rook(int old_x, int old_y, int new_x, int new_y, bool turn)
{
    int min, max;
    if( turn == 0 )
    {
        // If it's White's Turn, then insert Black's Piece range
        min = 0;
        max = 5;
    }
    else if( turn == 1)
    {
        // If it's Black's Turn, then insert White's Piece range
        min = 6;
        max = 11;
    }

    int team_min, team_max;
    if( turn == 0 )
    {
        // Range for White Pieces
        team_min = 6;
        team_max = 11;
    }
    else if( turn == 1)
    {
        // Range for Black Pieces
        team_min = 0;
        team_max = 5;
    }

    // Check Horizontal Movement
    if( old_y > 0)
    {
        // Left
        for(int i = old_y - 1; i >= 0; i-- )
        {
            // Tile is empty
            if( chess_board.board[old_x][i] == -1 )
            {
                if( (new_x == old_x) && (new_y == i))
                {
                    return 1;
                }
            }
            // Tile has Teammate
            if( chess_board.board[old_x][i] >= team_min && chess_board.board[old_x][i] <= team_max)
            {
                break;
            }
            // Tile has enemy
            if( chess_board.board[old_x][i] >= min && chess_board.board[old_x][i] <= max)
            {
                if( (new_x == old_x) && (new_y == i))
                {
                    return 1;
                }
                break;
            }
            
        }
    } 
    if( old_y < 7)
    {
        // Right
        for(int i = old_y + 1 ; i <= 7; i++ )
        {
            // Tile is empty
            if( chess_board.board[old_x][i] == -1 )
            {
                if( (new_x == old_x) && (new_y == i))
                {
                    return 1;
                }
            }
            // Tile has Teammate
            if( chess_board.board[old_x][i] >= team_min && chess_board.board[old_x][i] <= team_max)
            {
                break;
            }
            // Tile has enemy
            if( chess_board.board[old_x][i] >= min && chess_board.board[old_x][i] <= max)
            {
                if( (new_x == old_x) && (new_y == i))
                {
                    return 1;
                }
                break;
            }
            
        }
    } 

    // Check Vertical Movement
    if( old_x > 0)
    {
        // Up
        for(int i = old_x - 1; i >= 0; i-- )
        {
            // Tile is empty
            if( chess_board.board[i][old_y] == -1 )
            {
                if( (new_x == i) && (new_y == old_y))
                {
                    return 1;
                }
            }
            // Tile has Teammate
            if( chess_board.board[i][old_y] >= team_min && chess_board.board[i][old_y] <= team_max)
            {
                break;
            }
            // Tile has enemy
            if( chess_board.board[i][old_y] >= min && chess_board.board[i][old_y] <= max)
            {
                if( (new_x == i) && (new_y == old_y))
                {
                    return 1;
                }
                break;
            }
        }
    } 
    if( old_x < 7)
    {
        // Down
        for(int i = old_x + 1; i <= 7; i++ )
        {
            // Tile is empty
            if( chess_board.board[i][old_y] == -1 )
            {
                if( (new_x == i) && (new_y == old_y))
                {
                    return 1;
                }
            }
            // Tile has Teammate
            if( chess_board.board[i][old_y] >= team_min && chess_board.board[i][old_y] <= team_max)
            {
                break;
            }
            // Tile has enemy
            if( chess_board.board[i][old_y] >= min && chess_board.board[i][old_y] <= max)
            {
                if( (new_x == i) && (new_y == old_y))
                {
                    return 1;
                }
                break;
            }
        }
    }   


    return 0;
}

/*
Checks if Mouse clicked on a valid Tile for Bishop
*/
bool ChessWindow::bishop(int old_x, int old_y, int new_x, int new_y, bool turn)
{
    int min, max;
    if( turn == 0 )
    {
        // If it's White's Turn, then insert Black's Piece range
        min = 0;
        max = 5;
    }
    else if( turn == 1)
    {
        // If it's Black's Turn, then insert White's Piece range
        min = 6;
        max = 11;
    }

    int team_min, team_max;
    if( turn == 0 )
    {
        // Range for White Pieces
        team_min = 6;
        team_max = 11;
    }
    else if( turn == 1)
    {
        // Range for Black Pieces
        team_min = 0;
        team_max = 5;
    }

    int offset = 1;

    // Top Left 
    if( old_x > 0 && old_y > 0 )
    {
        while( (old_x - offset) >= 0 || (old_y - offset) >= 0)
        {
            // Tile is Empty
            if( chess_board.board[old_x - offset][old_y - offset] == -1 )
            {
                if((new_x == (old_x - offset)) && (new_y == (old_y - offset)))
                {
                    return 1;
                }
            }
            // Tile has Teammate
            if( chess_board.board[old_x - offset][old_y - offset] >= team_min && chess_board.board[old_x - offset][old_y - offset] <= team_max)
            {
                break;
            }
            // Tile has Enemy
            if( chess_board.board[old_x - offset][old_y - offset] >= min && chess_board.board[old_x - offset][old_y - offset] <= max)
            {
                if((new_x == (old_x - offset)) && (new_y == (old_y - offset)))
                {
                    return 1;
                }
                break;
            }
            offset++;
        }
    }
    // Top Right
    offset = 1;

    if( old_x > 0 && old_y < 7 )
    {
        while( (old_x - offset) >= 0 || (old_y + offset) <= 7 )
        {
            // Tile is Empty
            if( chess_board.board[old_x - offset][old_y + offset] == -1 )
            {
                if((new_x == (old_x - offset)) && (new_y == (old_y + offset)))
                {
                    return 1;
                }
            }
            // Tile has Teammate
            if( chess_board.board[old_x - offset][old_y + offset] >= team_min && chess_board.board[old_x - offset][old_y + offset] <= team_max)
            {
                break;
            }
            // Tile has Enemy
            if( chess_board.board[old_x - offset][old_y + offset] >= min && chess_board.board[old_x - offset][old_y + offset] <= max)
            {
                if((new_x == (old_x - offset)) && (new_y == (old_y + offset)))
                {
                    return 1;
                }
                break;
            }
            offset++;
        }
    }

    // Bottom Left
    offset = 1;

    if( old_x < 7 && old_y > 0)
    {
        while( (old_x + offset) <= 7 || (old_y - offset) >= 0 )
        {
            // Tile is Empty
            if( chess_board.board[old_x + offset][old_y - offset] == -1 )
            {
                if((new_x == (old_x + offset)) && (new_y == (old_y - offset)))
                {
                    return 1;
                }
            }
            // Tile has Teammate
            if( chess_board.board[old_x + offset][old_y - offset]  >= team_min && chess_board.board[old_x + offset][old_y - offset]  <= team_max)
            {
                break;
            }
            // Tile has Enemy
            if( chess_board.board[old_x + offset][old_y - offset]  >= min && chess_board.board[old_x + offset][old_y - offset]  <= max)
            {
                if((new_x == (old_x + offset)) && (new_y == (old_y - offset)))
                {
                    return 1;
                }
                break;
            }
            offset++;
        }
    }
    // Bottom Right
    offset = 1;

    if( old_x < 7 && old_y < 7)
    {
        while( (old_x + offset) <= 7 || (old_y + offset) <= 7 )
        {
            // Tile is Empty
            if( chess_board.board[old_x + offset][old_y + offset] == -1 )
            {
                if((new_x == (old_x + offset)) && (new_y == (old_y + offset)))
                {
                    return 1;
                }
            }
            // Tile has Teammate
            if( chess_board.board[old_x + offset][old_y + offset]  >= team_min && chess_board.board[old_x + offset][old_y + offset]  <= team_max)
            {
                break;
            }
            // Tile has Enemy
            if( chess_board.board[old_x + offset][old_y + offset]  >= min && chess_board.board[old_x + offset][old_y + offset]  <= max)
            {
                if((new_x == (old_x + offset)) && (new_y == (old_y + offset)))
                {
                    return 1;
                }
                break;
            }
            offset++;
        }
    }


    return 0;
}

/*
Checks if Mouse clicked on a valid Tile for Queen
*/
bool ChessWindow::queen(int old_x, int old_y, int new_x, int new_y, bool turn)
{
    return (rook(old_x, old_y, new_x, new_y, turn) || bishop( old_x, old_y, new_x, new_y, turn));
}

