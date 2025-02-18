#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
public:
    static constexpr float SPEED = 200.0f;
    Player(sf::Vector2i position);
    void update(float deltaTime, Grid& grid, sf::Vector2i playerPosition) override;
};

#endif // PLAYER_HPP