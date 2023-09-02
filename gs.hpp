#include <iostream>
#include <vector>
#include <utility>
#include <optional>
#include <tuple>
#include <algorithm>

class GaleShapley
{
private:
    int total_pairs;
    std::vector<std::string> gale_objects;
    std::vector<std::vector<std::string>> gale_preferences;
    std::vector<bool> gale_matches;

    std::vector<std::string> shapley_objects;
    std::vector<std::vector<std::string>> shapley_preferences;
    std::vector<std::string> shapley_matches;

public:
    GaleShapley(std::vector<std::string> g_obj, std::vector<std::string> s_obj, std::vector<std::vector<std::string>> g_pref, std::vector<std::vector<std::string>> s_pref)
    {
        gale_objects = g_obj;
        shapley_objects = s_obj;
        gale_preferences = g_pref;
        shapley_preferences = s_pref;

        total_pairs = gale_objects.size();

        // initialize empty vectors to keep current matches
        // vector of strings for shapleys, they will keep track of final matches
        std::vector<std::string> __sm(total_pairs, std::string("UNINITIALIZED"));
        // vector of booleans for gales, they will propose to their first available preference until everyone ends with a match
        std::vector<bool> __gm(total_pairs, bool(false));
        shapley_matches = __sm;
        gale_matches = __gm;
    }

    // validate 2 sides have same number of elements
    void validate_sizes()
    {
        if (gale_objects.size() != shapley_objects.size())
        {
            throw std::invalid_argument("Object vectors should be same size");
        }
    }

    // when shapley receives a proposal: checks the proposal against the current match (if any) using it's preference list
    // accepts proposal if new match is higher on the preference list
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

    // retrieve preference list for the shapley that is being proposed
    std::vector<std::string> get_shapley_preferences(int spos)
    {
        return shapley_preferences[spos];
    }

    // get index of an element in a vector
    int get_position(std::string object_name, std::vector<std::string> object_vector)
    {
        std::vector<std::string>::iterator s = std::find(object_vector.begin(), object_vector.end(),
                                                         object_name);
        int s_position = std::distance(object_vector.begin(), s);
        return s_position;
    }

    // retrieve the current match name
    std::string get_shapley_current_match(int spos)
    {
        return shapley_matches[spos];
    }

    // update gale's match to true of proposal was accepted
    // update gale's match to false if his existing proposal for broken due to better match
    void update_gale_match(bool new_match, int gale_obj_pos)
    {
        gale_matches[gale_obj_pos] = new_match;
    }

    // uddate shapley's match to the name of the latest proposal it accepted
    void update_shapley_match(std::string new_match, int shapley_obj_pos)
    {
        shapley_matches[shapley_obj_pos] = new_match;
    }

    // remove first element from gale's preferences if the proposal got rejected
    void remove_preference(int gale_obj_loc)
    {
        std::vector<std::string> gale_preference_list = gale_preferences[gale_obj_loc];
        gale_preference_list.erase(gale_preference_list.begin());
        gale_preferences[gale_obj_loc] = gale_preference_list;
    }

    // util to print final matches
    void print_matches(std::vector<std::pair<std::string, std::string>> p)
    {
        for (std::pair<std::string, std::string> i : p)
        {
            std::cout << i.first << '-' << i.second << std::endl;
        }
    }

    // run matching algorithm on 1 gale element
    void match(int gale)
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

    // run the whole process  until all gale matches are true
    std::vector<std::pair<std::string, std::string>> run()
    {
        try
        {
            validate_sizes();
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what();
            std::exit(1);
        }

        while (std::find(gale_matches.begin(), gale_matches.end(), false) != gale_matches.end())
        {
            for (int i = 0; i < gale_objects.size(); i++)
            {
                match(i);
            }
        }

        std::vector<std::pair<std::string, std::string>> gale_shapley_pairs(shapley_matches.size());
        for (unsigned i = 0; i < gale_shapley_pairs.size(); i++)
            gale_shapley_pairs[i] = std::make_pair(shapley_matches[i], shapley_objects[i]);
        return gale_shapley_pairs;
    }
};