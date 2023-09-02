#include <iostream>
#include <vector>
#include <utility>
#include <optional>
#include <tuple>
#include <algorithm>


std::vector<std::string> gale_objects = {"a", "b", "c"};
std::vector<std::vector<std::string>> gale_preferences = {{"e", "d", "f"}, {"f", "d", "e"}, {"f", "d", "e"}};
std::vector<bool> gale_matches = {false, false, false};

std::vector<std::string> shapley_objects = {"f", "d", "e"};
std::vector<std::vector<std::string>> shapley_preferences = {{"a", "b", "c"}, {"a", "b", "c"}, {"a", "b", "c"}};
std::vector<std::string> shapley_matches(3, std::string("UNINITIALIZED"));

bool check_match(std::vector<std::string> preferences, std::string new_match, std::string current_match)
{
    if (current_match != "UNINITIALIZED")
    {
        std::vector<std::string>::iterator it_old = std::find(preferences.begin(), preferences.end(), current_match);
        std::vector<std::string>::iterator it_new = std::find(preferences.begin(), preferences.end(), new_match);
        int current_position = std::distance(preferences.begin(), it_old);
        int new_position = std::distance(preferences.begin(), it_new);

        if (new_position < current_position)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

std::vector<std::string> get_shapley_preferences(int spos)
{
    return shapley_preferences[spos];
}

int get_position(std::string object_name, std::vector<std::string> object_vector)
{
    std::vector<std::string>::iterator s = std::find(object_vector.begin(), object_vector.end(),
                                                     object_name);
    int s_position = std::distance(object_vector.begin(), s);
    return s_position;
}

std::string get_shapley_current_match(int spos)
{
    return shapley_matches[spos];
}

void update_gale_match(bool new_match, int gale_obj_pos)
{
    gale_matches[gale_obj_pos] = new_match;
}

void update_shapley_match(std::string new_match, int shapley_obj_pos)
{
    shapley_matches[shapley_obj_pos] = new_match;
}

void remove_preference(int gale_obj_loc)
{
    std::vector<std::string> gale_preference_list = gale_preferences[gale_obj_loc];
    gale_preference_list.erase(gale_preference_list.begin());
    gale_preferences[gale_obj_loc] = gale_preference_list;
}

void gale_shapley(int gale)
{
    if (gale_matches[gale] == true)
    {
        return;
    }
    else
    {
        std::string current_pref = gale_preferences[gale].front();
        int shapley = get_position(current_pref, shapley_objects);
        std::vector<std::string> shapley_preference_list = get_shapley_preferences(shapley);
        std::string shapley_current_match = get_shapley_current_match(shapley);
        bool is_match = check_match(shapley_preference_list, gale_objects[gale], shapley_current_match);
        if (is_match == true)
        {
            update_shapley_match(gale_objects[gale], shapley);
            update_gale_match(true, gale);
            if (shapley_current_match != "UNINITIALIZED")
            {
                int prev_gale = get_position(shapley_current_match, gale_objects);
                update_gale_match(false, prev_gale);
            }
        }
        else
        {
            remove_preference(gale);
        }
    }
}

void main()
{

    while (std::find(gale_matches.begin(), gale_matches.end(), false) != gale_matches.end())
    {
        for (int i = 0; i < gale_objects.size(); i++)
        {
            gale_shapley(i);
        }
    }
    std::vector<std::pair<std::string, std::string>> gale_shapley_pairs(shapley_matches.size());

    for (unsigned i = 0; i < gale_shapley_pairs.size(); i++)
        gale_shapley_pairs[i] = std::make_pair(shapley_matches[i], shapley_objects[i]);


    for (std::pair<std::string, std::string> i : gale_shapley_pairs) {
        std::cout << i.first << '-' << i.second << std::endl;
    }
}
