#ifdef DEBUG

#include <assert.h>

#include <iostream>

namespace CP {

template <typename T1, typename T2>
class pair {
  public:
    T1 first;
    T2 second;

    // default constructor, using list initialize
    pair() : first(), second() {}

    // custom constructor, using list initialize
    pair(const T1& a, const T2& b) : first(a), second(b) {}

    // we have no destructor

    // equality operator
    bool operator==(const pair<T1, T2>& other) {
        std::cout << "You cannot call operator==" << std::endl;
        assert(false);
    }

    // comparison operator
    bool operator<(const pair<T1, T2>& other) const {
        std::cout << "You cannot call operator<" << std::endl;
        assert(false);
    }

    bool operator>=(const pair<T1, T2>& other) const;
};

}  // namespace CP

#endif

#pragma region student.h
#ifndef __STUDENT_H_
#define __STUDENT_H_

template <typename T1, typename T2>
bool CP::pair<T1, T2>::operator>=(const pair<T1, T2>& other) const {
    return this->first > other.first ||
           (this->first == other.first && this->second >= other.second);
}

#endif
#pragma endregion student.h
