#include <time.h>
#include <SFML/Graphics.hpp>

int WIDTH = 32;
int GRID[12][12];
int SHOWN[12][12];


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

    for(int i = 1; i <=10; ++i) {
        for(int j = 1; j <=10; ++j) {
            SHOWN[i][j] = 10;
        }
    }

    while(window.isOpen()) {
        // Process events
        sf::Event e;
        while (window.pollEvent((e))) {
            // Handle closing
            if (e.type == sf::Event::Closed) { window.close(); }
        }
        // Draw grid
        window.clear(sf::Color::White);

        for(int i = 1; i <=10; ++i) {
            for(int j = 1; j <=10; ++j) {
                tiles.setTextureRect(sf::IntRect(SHOWN[i][j] * WIDTH, 0, WIDTH, WIDTH));
                tiles.setPosition(i * WIDTH, j * WIDTH);
                window.draw(tiles);
            }
        }
        window.display();
    }

    return 0;
}
