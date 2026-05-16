#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace notepad_sort {
    inline void sort_by_word(std::vector<std::pair<std::string, int> > &entries) {
        std::sort(entries.begin(), entries.end(),
                  [](const auto &a, const auto &b) { return a.first < b.first; });
    }

    inline void sort_by_frequency(std::vector<std::pair<std::string, int> > &entries) {
        std::sort(entries.begin(), entries.end(), [](const auto &a, const auto &b) {
            return a.second != b.second ? a.second > b.second : a.first < b.first;
        });
    }
}

#endif // SORT_H
