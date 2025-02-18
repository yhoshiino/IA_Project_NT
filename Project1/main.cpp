#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "EnemyFSM.hpp"
#include "Grid.hpp"
#include "State.hpp"
#include "PatrolAction.hpp"
#include "FollowAction.hpp"
#include "AttackAction.hpp"
#include "FleeAction.hpp"
#include "Planner.hpp"
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

    Player player(Vector2f(200, 400));
    vector<shared_ptr<EnemyGoap>> enemies = {
        make_shared<EnemyGoap>(Vector2f(100, 100), false, false, false)
    };

    for (State& state : testStates) {
        shared_ptr<Action> action = Plan(state, actions);
        if (action) {
            action->Execute(state);
        }
        else {
            cout << "No action can be executed.\n";
        }
    }


    Player player(Vector2i(6, 11));
    EnemyFSM FSM(Vector2i(3, 3), 1.f);
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
        window.draw(FSM.shape);
        FSM.update(deltaTime, grid, player.position);

            
        window.display();
    }
    return 0;
}
