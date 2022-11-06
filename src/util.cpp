#include "util.hpp"

namespace util {
    std::pair<int, int> find_min_positive_in_2d_array(ds::array_list<ds::array_list<int>> &a) {
        int min = std::numeric_limits<int>::max();
        std::pair<int, int> location;

        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a.at(0).size(); ++j) {
                if (a[i][j] < min && a[i][j] > 0) {
                    min = a[i][j];
                    location = std::make_pair(i, j);
                }
            }
        }
        
        return location;
    }

    bool contains_negative_int(ds::array_list<ds::array_list<int>> a) {
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a.at(0).size(); ++j) {
                if (a[i][j] > 0) {
                    return false;
                }
            }
        }
        return true;
    }
}
