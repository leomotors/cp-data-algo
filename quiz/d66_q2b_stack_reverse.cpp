#ifndef __STUDENT_H_
#define __STUDENT_H_

#include <algorithm>

#include "stack.h"

template <typename T>
void CP::stack<T>::reverse(size_t first, size_t last) {
    // write your code here
    if (first >= last) return;

    first = std::max(first, static_cast<size_t>(0));
    last = std::min(last, mSize - 1);
    int width = last - first;

    for (int i = 0; i <= width / 2; i++) {
        std::swap(mData[mSize - 1 - first - i], mData[mSize - 1 - last + i]);
    }
}

#endif
