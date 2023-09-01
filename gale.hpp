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
    std::vector<std::string> remove_preference(std::vector<std::string>);
    std::string send_match(std::vector<std::string>);
};

void Gale::add_preference(std::vector<std::string> new_preference)
{
    preferences = new_preference;
}

std::vector<std::string> Gale::remove_preference(std::vector<std::string> preference_list){
     preference_list.erase(preference_list.begin());
     return preference_list;
    }

std::string Gale::send_match(std::vector<std::string> preference_list)
{
    return preference_list.front();
}
