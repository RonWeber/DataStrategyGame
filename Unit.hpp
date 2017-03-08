#include "json.hpp"

using json = nlohmann::json;
using string=std::string;

class Unit {
public:
    int id;
    std::map<string, int> data_keys;
    char unitTypeID;
    std::vector<string> abilities;

    json toJSON();
};
