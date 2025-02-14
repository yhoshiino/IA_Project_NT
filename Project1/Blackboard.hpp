#include <unordered_map>
#include <string>

class Blackboard {
private:
    std::unordered_map<std::string, int> data;
public:
    void SetValue(const std::string& key, int value) {
        data[key] = value;
    }
    int GetValue(const std::string& key) {
        return data[key];
    }
};