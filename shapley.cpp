#include "shapley.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

void Shapley::add_preference(std::vector<std::string> new_preference)
{
    preferences = new_preference;
}

void Shapley::check_match(std::string new_match)
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
        }
    }
    else
    {
        current_match = new_match;
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
