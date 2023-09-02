#include "gs.hpp"

#include <iostream>
#include <vector>
#include <utility>
#include <optional>
#include <tuple>
#include <algorithm>

// 2 sides (men and women in the original paper, where the gale_objects side sends proporals)
std::vector<std::string> gale_objects = {"a", "b", "c"};
std::vector<std::string> shapley_objects = {"f", "d", "e"};

// complete and non-repeating list of preferences for each object
std::vector<std::vector<std::string>> gale_pref = {{"e", "d", "f"}, {"f", "d", "e"}, {"f", "d", "e"}};
std::vector<std::vector<std::string>> shapley_pref = {{"a", "b", "c"}, {"a", "b", "c"}, {"a", "b", "c"}};

// the algorithm will check if 2 objects have same length and run stable matching until all gale (proposing sides) have a match
// this should satifsy stable matching because gales will always propose (1) to their first prefrences and (2) until they have a match
void main()
{
    GaleShapley gshap(gale_objects, shapley_objects, gale_pref, shapley_pref); // todo: validate for non-duplicate preferences
    std::vector<std::pair<std::string, std::string>> pairs = gshap.run();
    gshap.print_matches(pairs);
}
