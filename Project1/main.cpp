#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "State.hpp"
#include "PatrolAction.hpp"
#include "FollowAction.hpp"
#include "AttackAction.hpp"
#include "FleeAction.hpp"
#include "Planner.hpp"
#include <vector>
#include <memory>

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    // Initialize actions
    vector<shared_ptr<Action>> actions = {
        make_shared<PatrolAction>(),
        make_shared<FollowAction>(),
        make_shared<AttackAction>(),
        make_shared<FleeAction>()
    };

    // Test different states
    vector<State> testStates = {
        State(false, false, false), // Patrolling
        State(true, false, false),  // Following
        State(true, true, false),   // Attacking
        State(true, true, true)     // Fleeing
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


    Player player(Vector2f(200, 400));
    vector<Enemy> enemies = { Enemy(Vector2f(100, 100)), Enemy(Vector2f(700, 100)) };
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

        player.update(deltaTime, grid);
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid);
        }

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (const auto& enemy : enemies)
            window.draw(enemy.shape);
        window.display();
    }
    return 0;
}

