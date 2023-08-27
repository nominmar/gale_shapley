#include <iostream>
#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>

class Gale
{
private:
    std::vector<std::string> preferences;
    std::optional<std::string> current_match;

public:
    std::string gale;
    void add_preference(std::vector<std::string>);
    bool send_match();
};

void Gale::add_preference(std::vector<std::string> new_preference)
{
    preferences = new_preference;
}