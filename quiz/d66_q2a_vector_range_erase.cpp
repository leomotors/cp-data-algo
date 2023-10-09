#ifndef __STUDENT_H_
#define __STUDENT_H_

// You can include library here
#include <algorithm>
#include <vector>

#include "vector.h"

template <typename T>
void CP::vector<T>::range_erase(
    std::vector<std::pair<iterator, iterator>> &ranges) {
    std::vector<T> result;

    std::sort(ranges.begin(), ranges.end());

    auto rangeIt = ranges.begin();

    for (auto it = this->begin(); it < this->end(); it++) {
        while (rangeIt != ranges.end() && it >= rangeIt->second) {
            rangeIt++;
        }

        if (rangeIt == ranges.end()) {
            result.push_back(*it);
            continue;
        }

        if (it >= rangeIt->first && it < rangeIt->second) {
            continue;
        }

        result.push_back(*it);
    }

    for (int i = 0; i < result.size(); i++) {
        mData[i] = result[i];
    }

    mSize = result.size();
}

#endif
