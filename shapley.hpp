#include <iostream>
#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>

class Shapley
{
private:
    std::vector<std::string> preferences;
    std::optional<std::string> current_match;

public:
    std::string shapley;
    void add_preference(std::vector<std::string>);
    bool check_match(std::string);
    void show_preferences();
    void show_current_match();
};

void Shapley::add_preference(std::vector<std::string> new_preference)
{
    preferences = new_preference;
}

bool Shapley::check_match(std::string new_match)
{
    if (current_match.has_value())
    {
        std::vector<std::string>::iterator it_old = std::find(preferences.begin(), preferences.end(), current_match);
        std::vector<std::string>::iterator it_new = std::find(preferences.begin(), preferences.end(), new_match);
        int current_position = std::distance(preferences.begin(), it_old);
        int new_position = std::distance(preferences.begin(), it_new);

        if (new_position < current_position)
        {
            current_match = new_match;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        current_match = new_match;
        return true;
    }
}
void Shapley::show_preferences()
{
    for (std::string i : preferences)
        std::cout << i << ' ';
}

void Shapley::show_current_match()
{
    if (current_match.has_value())
    {
        std::cout << current_match.value();
    }
    else
    {
        std::cout << "No match has been made yet";
    }
}
