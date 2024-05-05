#include "Mapa.h"

Map mapa[HEIGHT][WIDTH];

 Map::Map() 
    {
        // Initialize the number of pokemons left in each zone
        pokemonsLeftInZone = { MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_1,
                              MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_2,
                              MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_3,
                              MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_4 };
    }

void Map::InitializeMap(Ash& player)
{
    
    // Clear the map
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            mapa[i][j].typeCell = TypeOfCell::EMPTY;
        }
    }

    for (int i = 0; i < WIDTH; i++)
    {
        mapa[0][i].typeCell = TypeOfCell::WALL;
        mapa[HEIGHT-1][i].typeCell = TypeOfCell::WALL;
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        mapa[i][0].typeCell = TypeOfCell::WALL;
        mapa[i][WIDTH-1].typeCell = TypeOfCell::WALL;
    }

    // Create cross walls
    for (int i = 0; i < HEIGHT; i++) {
        mapa[i][WIDTH / 2].typeCell = TypeOfCell::WALL;
    }
    for (int i = 0; i < WIDTH; i++) {
        mapa[HEIGHT / 2][i].typeCell = TypeOfCell::WALL;
    }

    // Initialize Pokémon in zones 
    InitializePokemonsInZone(0, HEIGHT / 2, 0, WIDTH / 2, MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_1); // Zone 1
    InitializePokemonsInZone(0, HEIGHT / 2, WIDTH / 2, WIDTH, MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_2); // Zone 2
    InitializePokemonsInZone(HEIGHT / 2, HEIGHT, WIDTH / 2, WIDTH, MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_3); // Zone 3
    InitializePokemonsInZone(HEIGHT / 2, HEIGHT, 0, WIDTH / 2, MIN_NUM_POKEMONS_TO_CAPTURE_IN_ZONE_4); // Zone 4

    // Place player randomly
    SetPlayerPosition(player);
}

void Map::InitializePokemonsInZone(int startX, int endX, int startY, int endY, int numPokemons)
{
    int row, column;
    for (int i = 0; i < numPokemons; i++) {
        do {
            row = rand() % (endX - startX) + startX;
            column = rand() % (endY - startY) + startY;
        } while (mapa[row][column].typeCell != TypeOfCell::EMPTY);
        mapa[row][column].typeCell = TypeOfCell::POKEMON;
    }
}

void Map::SetPlayerPosition(Ash& player)
{
    int row, column;
    do {
        row = rand() % (HEIGHT / 2);  // Restrict to zone 1 (left half of the map)
        column = rand() % (WIDTH / 2);  // Restrict to zone 1 (top half of the map)
    } while (mapa[row][column].typeCell != TypeOfCell::EMPTY);
    mapa[row][column].typeCell = TypeOfCell::PLAYER;
    player.SetPos(Position2D(row, column));
}


void Map::OpenGate1(Ash& player)
{
    for (int i = 0; i < HEIGHT / 2; i++) {
        mapa[i][WIDTH / 2].typeCell = TypeOfCell::EMPTY;
    }
}

void Map::OpenGate2(Ash& player)
{
    for (int i = WIDTH / 2; i < WIDTH; i++) {
        mapa[HEIGHT/2][i].typeCell = TypeOfCell::EMPTY;
    }
}

void Map::OpenGate3(Ash& player)
{
    for (int i = HEIGHT / 2; i < HEIGHT; i++) {
        mapa[i][WIDTH/2].typeCell = TypeOfCell::EMPTY;
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

//es lo mateix q ficar max i min amb la llibreria algorithm
int MAX(int a, int b) {
    return (a > b) ? a : b;
}

int MIN(int a, int b) {
    return (a < b) ? a : b;
}



void Map::PrintBoard(Ash& player) {
    
    int startRow, endRow, startCol, endCol;

    if (player.GetPos().x - (VIEW_HEIGHT / 2) > 0) {
        startRow = player.GetPos().x - (VIEW_HEIGHT / 2);
    }
    else {
        startRow = 0;
    }

    if (player.GetPos().x + (VIEW_HEIGHT / 2) < HEIGHT) {
        endRow = player.GetPos().x + (VIEW_HEIGHT / 2);
    }
    else {
        endRow = HEIGHT - 1;
    }

    if (player.GetPos().y - (VIEW_WIDTH / 2) > 0) {
        startCol = player.GetPos().y - (VIEW_WIDTH / 2);
    }
    else {
        startCol = 0;
    }

    if (player.GetPos().y + (VIEW_WIDTH / 2) < WIDTH) {
        endCol = player.GetPos().y + (VIEW_WIDTH / 2);
    }
    else {
        endCol = WIDTH - 1;
    }

    
    for (int i = startRow; i <= endRow; ++i) {
        for (int j = startCol; j <= endCol; ++j) {
            switch (mapa[i][j].typeCell) {
            case TypeOfCell::PLAYER:
                switch (player.GetDirection()) {
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
                std::cout << (char)219; // Wall
                break;
            case TypeOfCell::POKEMON:
                std::cout << (char)157; // Pokemon
                break;
            case TypeOfCell::EMPTY:
                std::cout << " "; // Empty space
                break;
            }
        }
        std::cout << std::endl; // Newline after each row
    }
}





   bool Map::GameOver() {
       // Count the number of captured pokemons
       int capturedPokemons = 0;
       for (int i = 0; i < HEIGHT; ++i) {
           for (int j = 0; j < WIDTH; ++j) {
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

    // Determine the position of the next step
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

    // Check if there's a Pokémon in the next position
    if (mapa[nextPos.x][nextPos.y].typeCell == TypeOfCell::POKEMON) {
        // Capture the Pokémon
        player.setPokemonsCaptured(0);

        // Update the captured Pokémon's cell to empty
        mapa[nextPos.x][nextPos.y].typeCell = TypeOfCell::EMPTY;

        // Print a message
        std::cout << "You captured a Pokemon!" << std::endl;

        // Update the count of remaining Pokémon in the corresponding zone
        if (nextPos.x < HEIGHT / 2 && nextPos.y < WIDTH / 2) {
            pokemonsLeftInZone[0]--;
        }
        else if (nextPos.x < HEIGHT / 2 && nextPos.y >= WIDTH / 2) {
            pokemonsLeftInZone[1]--;
        }
        else if (nextPos.x >= HEIGHT / 2 && nextPos.y < WIDTH / 2) {
            pokemonsLeftInZone[3]--;
        }
        else {
            pokemonsLeftInZone[2]--;
        }

        // Check if the count for a zone reaches zero, and if so, open the gate for that zone
        if (pokemonsLeftInZone[0] == 0) {
            OpenGate1(player);
        }
        if (pokemonsLeftInZone[1] == 0) {
            OpenGate2(player);
        }
        if (pokemonsLeftInZone[2] == 0) {
            OpenGate3(player);
        }
    }
    else {
        std::cout << "There is no Pokemon to capture." << std::endl;
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

    // Debug output
    std::cout << "New position: (" << newPos.x << ", " << newPos.y << ")" << std::endl;

    // Check if the new position is valid
    if (newPos.x >= 0 && newPos.x < HEIGHT && newPos.y >= 0 && newPos.y < WIDTH) {
        // Update the player's position
        player.SetPos(newPos);

        // Clear the previous position of the player
        mapa[currentPos.x][currentPos.y].typeCell = TypeOfCell::EMPTY;

        // Update the game board with the new position of the player
        mapa[newPos.x][newPos.y].typeCell = TypeOfCell::PLAYER;
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

    // Debug output
    std::cout << "New position: (" << newRow << ", " << newColumn << ")" << std::endl;

    // Check if the new position is out of bounds
    if (newRow < 0 || newRow >= HEIGHT || newColumn < 0 || newColumn >= WIDTH) {
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

    // Check if the new position is a gate that was opened
    if (mapa[newRow][newColumn].typeCell == TypeOfCell::EMPTY) {
        return true;
    }

    // Allow movement if none of the above conditions are met
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