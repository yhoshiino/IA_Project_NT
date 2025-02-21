#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "EnemyFSM.hpp"
#include "Grid.hpp"
#include "EnemyGoap.hpp"
#include <vector>
#include <memory>

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(Vector2i(6, 11));
    EnemyFSM FSM(Vector2i(3, 3), 200.f, 200.f);
    EnemyGoap goap(Vector2i(3, 3), false, false, false, 150.f,300.f, 150.f);
    Grid grid;
    grid.loadFromFile("map.txt");

    Clock clock;

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid, player.position);
        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        /*window.draw(FSM.shape);
        FSM.updateFSM(deltaTime, grid, player);*/
        window.draw(goap.shape);
        goap.updateGoap(deltaTime, grid, player);

            
        window.display();
    }
    return 0;
}
