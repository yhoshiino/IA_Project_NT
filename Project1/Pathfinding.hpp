#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "Grid.hpp"
#include "Node.hpp"
#include <vector>
using namespace std;
using namespace sf;

class Pathfinding {
public:
    static std::vector<sf::Vector2i> findPath(Grid& grid, sf::Vector2i start, sf::Vector2i end);
};

#endif
