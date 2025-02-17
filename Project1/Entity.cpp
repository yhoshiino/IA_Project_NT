#include "Entity.hpp"

Entity::Entity(sf::Vector2f position, sf::Color color) {
    shape.setSize({ 35, 35 });
    shape.setPosition(position);
    shape.setFillColor(color);
}
