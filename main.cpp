#include <time.h>
#include <functional>
#include <SFML/Graphics.hpp>

int WIDTH = 32;
int GRID[12][12];
int SHOWN[12][12];

// Relative positions of surrounding cells
int HINT_GRID[8][2] = {
    {-1, -1},   {0, -1},    {1, -1},
    {-1, 0},    /*0, 0*/    {1, 0},
    {-1, 1},    {0, 1},     {1, 1}
};

// Run a loop through the whole grid and call passed function on column-&-row indexes
void gridLoop(std::function<void(int, int)>func) {  // void (*func)(int, int)
    for(int i = 1; i <=10; ++i) {
        for(int j = 1; j <=10; ++j) {
            func(i, j);
        }
    }
}

void hints(int i, int j) {
    // Skip bomb cells
    if(GRID[i][j] == 9) { return; }
    int counter = 0;

    // Count number of bombs in surrounding cells
    for (auto position : HINT_GRID) {
        if(GRID[i + position[0]][j + position[1]] == 9) {
            ++counter;
        }
    }
    // Set proper hint number in GRID
    GRID[i][j] = counter;
}


int main()
{
    // Init random engine
    srand(time(0));

    // Create window
    sf::RenderWindow window(sf::VideoMode(400, 400), "Minesweeper");

    // Load tile sprite
    sf::Texture texture;
    texture.loadFromFile("assets/tiles.jpg");
    sf::Sprite tiles(texture);

    // Initialize GRID and SHOWN matrices with proper values
    gridLoop([] (int i, int j) {
        SHOWN[i][j] = 10;
        // Randomly set as bomb or empty
        (rand() % 5 == 0) ? GRID[i][j] = 9 : GRID[i][j] = 0;
    });
    gridLoop(&hints);

    // Main loop
    while(window.isOpen()) {
        // Process events
        sf::Event e;
        while (window.pollEvent((e))) {
            // Handle closing
            if (e.type == sf::Event::Closed) { window.close(); }
        }
        // Draw grid
        window.clear(sf::Color::White);
        gridLoop([&tiles, &window] (int i, int j) {
            // Choose proper tile to draw and display it at position
            // TODO SHOWN[i][j] = GRID[i][j];
            tiles.setTextureRect(sf::IntRect(SHOWN[i][j] * WIDTH, 0, WIDTH, WIDTH));
            tiles.setPosition(i * WIDTH, j * WIDTH);
            window.draw(tiles);
        });

        window.display();
    }

    return 0;
}
