#ifndef __STUDENT_H_
#define __STUDENT_H_

#include <algorithm>
#include <cmath>
#include <vector>

#include "queue.h"

template <typename T>
void CP::queue<T>::v_split(std::vector<std::queue<T>> &output, size_t k) const {
    int it = 0;

    while (k) {
        std::queue<T> curr;

        int targetSize = std::ceil((mSize - it) * 1.0 / k);

        for (int i = 0; i < targetSize; i++) {
            curr.push(mData[(mFront + it + i) % mCap]);
        }

        it += targetSize;
        output.push_back(curr);
        k--;
    }
}

#endif
