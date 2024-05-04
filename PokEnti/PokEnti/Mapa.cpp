#include "Mapa.h"

Map mapa[WIDTH][HEIGHT];


void Map::InitializeMap(Ash& player)
{


    int row, column;
    for ( int i = 0;  i < WIDTH;  i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
           // newPanel[i].myColor = static_cast<ColourBall>(std::rand() % static_cast<int>(ColourBall::COUNT));
            mapa[i][j].typeCell = static_cast<TypeOfCell>(TypeOfCell::EMPTY);
       
        }
    }
  
    for (int i = 0; i < WIDTH; i++)
    {
        mapa[i][WIDTH/2].typeCell = static_cast<TypeOfCell>(TypeOfCell::WALL);
    }
 
    for (int i = 0; i < HEIGHT; i++)
    {
        mapa[HEIGHT / 2][i].typeCell = static_cast<TypeOfCell>(TypeOfCell::WALL);
    }

    for (int i = 0; i < MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_1; i)
    {
        row = rand() % (WIDTH / 2);
        column = rand() % (HEIGHT/ 2);
        if (mapa[row][column].typeCell == TypeOfCell::EMPTY)
        {
            mapa[row][column].typeCell = static_cast<TypeOfCell> (TypeOfCell::POKEMON);
            i++;
        }
    }

    for (bool displayPlayer = false; !displayPlayer;)
    {
        row = rand() % (WIDTH / 2);
        column = rand() % (HEIGHT / 2);
        if (mapa[row][column].typeCell == TypeOfCell::EMPTY)
        {
            mapa[row][column].typeCell = TypeOfCell::PLAYER;
            Position2D newPos(row, column); 
            player.SetPos(newPos); 
            player.SetDirection('v'); 
            displayPlayer = true; 
        }
    }

    

}

void Map::SetPos(Ash& player, Movement move)
{
    Position2D currentPos = player.GetPos();

    // Update the position based on the specified movement
    switch (move)
    {
    case Movement::UP:
        currentPos.x--;
        break;
    case Movement::DOWN:
        currentPos.x++;
        break;
    case Movement::LEFT:
        currentPos.y--;
        break;
    case Movement::RIGHT:
        currentPos.y++;
        break;
    }

    // Set the new position for the player
    player.SetPos(currentPos);
}


void Map::PrintBoard(Ash& player)
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            switch (mapa[i][j].typeCell)
            {
            case TypeOfCell::PLAYER:
                switch (player.GetDirection())
                {
                case 'v':
                    std::cout << "v"; // Downwards
                    break;
                case '^':
                    std::cout << "^"; // Upwards
                    break;
                case '<':
                    std::cout << "<"; // Left
                    break;
                case '>':
                    std::cout << ">"; // Right
                    break;
                }
                break;
            case TypeOfCell::WALL:
                std::cout << "X"; // Wall
                break;
            case TypeOfCell::POKEMON:
                std::cout << "p"; // Pokemon
                break;
            case TypeOfCell::EMPTY:
                std::cout << " "; // Empty space
                break;
            }
        }
        std::cout << std::endl; // Newline after each row
    }
}



bool Map::CheckMovement(const Ash& player, Movement move) {
    Position2D currentPos = player.GetPos();
    int newRow = currentPos.x, newColumn = currentPos.y;

    // Calculate the new position based on the movement
    switch (move) {
    case Movement::UP:
        newRow--;
        break;
    case Movement::DOWN:
        newRow++;
        break;
    case Movement::LEFT:
        newColumn--;
        break;
    case Movement::RIGHT:
        newColumn++;
        break;
    }

    // Check if the new position is out of bounds
    if (newRow < 0 || newRow >= WIDTH || newColumn < 0 || newColumn >= HEIGHT) {
        std::cout << "The movement is invalid, try another." << std::endl;
        return false;
    }

    // Check if the new position is occupied by a wall
    if (mapa[newRow][newColumn].typeCell == TypeOfCell::WALL) {
        std::cout << "There's a wall blocking the way." << std::endl;
        return false;
    }

    // Check if the new position is occupied by a Pokemon
    if (mapa[newRow][newColumn].typeCell == TypeOfCell::POKEMON) {
        std::cout << "There's a Pokemon in the way! You cannot move there." << std::endl;
        return false;
    }

    return true;
}




void Map::SetMovement(Ash& player, Movement& move) {
    // Check for user input and update direction accordingly
    if (GetAsyncKeyState(VK_UP)) {
        player.SetDirection('^');
        move = Movement::UP;
    }
    else if (GetAsyncKeyState(VK_DOWN)) {
        player.SetDirection('v');
        move = Movement::DOWN;
    }
    else if (GetAsyncKeyState(VK_LEFT)) {
        player.SetDirection('<');
        move = Movement::LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT)) {
        player.SetDirection('>');
        move = Movement::RIGHT;
    }
}



   void Map::MovementAsh(Ash& player, Movement move) {
       Position2D currentPos = player.GetPos();
       Position2D newPos = currentPos;

       // Update the position based on the specified movement
       switch (move) {
       case Movement::UP:
           newPos.x--;
           break;
       case Movement::DOWN:
           newPos.x++;
           break;
       case Movement::LEFT:
           newPos.y--;
           break;
       case Movement::RIGHT:
           newPos.y++;
           break;
       }

       // Check if the new position is valid
       if (newPos.x >= 0 && newPos.x < WIDTH && newPos.y >= 0 && newPos.y < HEIGHT) {
           // Update the player's position
           player.SetPos(newPos);

           // Clear the previous position of the player
           mapa[currentPos.x][currentPos.y].typeCell = TypeOfCell::EMPTY;

           // Update the game board with the new position of the player
           mapa[newPos.x][newPos.y].typeCell = TypeOfCell::PLAYER;
       }
   }




bool Map::GameOver() {
    // Count the number of captured pokemons
    int capturedPokemons = 0;
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            if (mapa[i][j].typeCell == TypeOfCell::POKEMON) {
                capturedPokemons++;
            }
        }
    }

    // Check if all the pokemons have been captured
    return (capturedPokemons == 0);
}


void Map::CapturePokemon(Ash& player) {
    
    Position2D currentPos = player.GetPos();

   
    Position2D nextPos = currentPos;
    switch (player.GetDirection()) {
    case '^':
        nextPos.x--;
        break;
    case 'v':
        nextPos.x++;
        break;
    case '<':
        nextPos.y--;
        break;
    case '>':
        nextPos.y++;
        break;
    }

    
    if (mapa[nextPos.x][nextPos.y].typeCell == TypeOfCell::POKEMON) {
       
        player.CapturedPokemons(player);

        
        mapa[nextPos.x][nextPos.y].typeCell = TypeOfCell::EMPTY;

       
        std::cout << "You captured a Pokemon!" << std::endl;
    }
    else {
        std::cout << "There is no Pokemon to capture." << std::endl;
    }
}
