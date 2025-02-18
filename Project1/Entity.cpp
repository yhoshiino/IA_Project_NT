#include "Entity.hpp"

Entity::Entity(sf::Vector2i position, sf::Color color, float speed) : position(position), Speed(speed) {
    shape.setSize({ 40, 40 });
    shape.setPosition(sf::Vector2f(position.x * 40, position.y * 40));
    shape.setFillColor(color);
}
