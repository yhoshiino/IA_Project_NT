#include <iostream>
#include <vector>
#include <memory>
#include "BTNode.hpp"
#include "blackboard.hpp"
class ConditionNode : public BTNode {
private:
    Blackboard& blackboard;
    std::string key;
    int expectedValue;
public:
    ConditionNode(Blackboard& bb, const std::string& key, int value) : blackboard(bb), key(key), expectedValue(value) {}
    NodeState execute() override {
        return (blackboard.GetValue(key) == expectedValue) ? NodeState::SUCCESS : NodeState::FAILURE;
    }
};

class ActionNode : public BTNode {
private:
    std::string actionName;
public:
    ActionNode(std::string name) : actionName(name) {}
    NodeState execute() override {
        std::cout << "Action: " << actionName << std::endl;
        return NodeState::SUCCESS;
    }
};