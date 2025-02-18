#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
using namespace std;
using namespace sf;

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2i position;
    Entity(sf::Vector2i position, sf::Color color);
    virtual void update(float deltaTime, Grid& grid, sf::Vector2i playerPosition) = 0;
};

#endif // ENTITY_HPP