#include <iostream>
#include <vector>
#include <optional>


class Shapley{
    std::vector<std::string> preferences;
    std::optional<std::string> current_match;

public:
    void add_preference(std::vector<std::string>);
    void check_match(std::string);
    void show_preferences();
    void show_current_match();

};
