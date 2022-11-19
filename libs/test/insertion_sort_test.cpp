#include "insertion_sort.hpp"
#include "array_list.hpp"
#include <algorithm>
#include <functional>


int main() {
    ds::array_list<int> a = {3, 4, 9, 1, 8, 7, 4, 3, -10, 100, -20, 300};

    algo::sort::insertion_sort(a.begin(), a.end());

    if (!std::is_sorted(a.begin(), a.end())) {
        return 1;
    }

    ds::array_list<int> b = {3, 4, 9, 1, 8, 7, 4, 3, -10, 100, -20, 300};

    algo::sort::insertion_sort(b.begin(), b.end(), std::greater<int>());

    if (!std::is_sorted(b.begin(), b.end(), std::greater<int>())) {
        return 1;
    }

    return 0;
}