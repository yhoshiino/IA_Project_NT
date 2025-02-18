#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
using namespace std;
using namespace sf;

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f position;
    Entity(sf::Vector2f position, sf::Color color);
    virtual void update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) = 0;
};

#endif // ENTITY_HPP