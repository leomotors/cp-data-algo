#ifndef __STUDENT_H_
#define __STUDENT_H_

// You can include library here
#ifndef DEBUG
#include "stack.h"
#endif

#include <cmath>

template <typename T>
void CP::stack<T>::v_split(std::vector<std::stack<T>>& output, size_t k) const {
    int maxMember = std::ceil(mSize * 1.0 / k);

    int endPtr = mSize;
    for (int i = 0; i < k; i++) {
        std::stack<T> a;

        maxMember = std::ceil(endPtr * 1.0 / (k - i));

        for (int j = 0; j < maxMember; j++) {
            int position = endPtr - (maxMember - j);
            if (position >= 0) {
                a.push(mData[position]);
            }
        }

        endPtr -= maxMember;

        output.push_back(a);
    }
}

#endif
