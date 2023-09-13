#ifndef _CP_VECTOR_INCLUDED_
#define _CP_VECTOR_INCLUDED_

#include <iostream>
#include <stdexcept>
//#pragma once

namespace CP {

template <typename T>
class vector {
  public:
    typedef T* iterator;

  protected:
    T* mData;
    size_t mCap;
    size_t mSize;

    void rangeCheck(int n) {
        if (n < 0 || (size_t)n >= mSize) {
            throw std::out_of_range("index of out range");
        }
    }

    void expand(size_t capacity) {
        T* arr = new T[capacity]();
        for (size_t i = 0; i < mSize; i++) {
            arr[i] = mData[i];
        }
        delete[] mData;
        mData = arr;
        mCap = capacity;
    }

    void ensureCapacity(size_t capacity) {
        if (capacity > mCap) {
            size_t s = (capacity > 2 * mCap) ? capacity : 2 * mCap;
            expand(s);
        }
    }

  public:
    //-------------- constructor & copy operator ----------

    // copy constructor
    vector(const vector<T>& a) {
        mData = new T[a.capacity()]();
        mCap = a.capacity();
        mSize = a.size();
        for (size_t i = 0; i < a.size(); i++) {
            mData[i] = a[i];
        }
    }

    // default constructor
    vector() {
        int cap = 1;
        mData = new T[cap]();
        mCap = cap;
        mSize = 0;
    }

    // constructor with initial size
    vector(size_t cap) {
        mData = new T[cap]();
        mCap = cap;
        mSize = cap;
    }

    // copy assignment operator using copy-and-swap idiom
    vector<T>& operator=(vector<T> other) {
        // other is copy-constructed which will be destruct at the end of this
        // scope we swap the content of this class to the other class and let it
        // be descructed
        using std::swap;
        swap(this->mSize, other.mSize);
        swap(this->mCap, other.mCap);
        swap(this->mData, other.mData);
        return *this;
    }

    ~vector() {
        delete[] mData;
    }

    //------------- capacity function -------------------
    bool empty() const {
        return mSize == 0;
    }

    size_t size() const {
        return mSize;
    }

    size_t capacity() const {
        return mCap;
    }

    void resize(size_t n) {
        if (n > mCap) expand(n);

        if (n > mSize) {
            T init = T();
            for (size_t i = mSize; i < n; i++) mData[i] = init;
        }

        mSize = n;
    }

    //----------------- iterator ---------------
    iterator begin() {
        return &mData[0];
    }

    iterator end() {
        return begin() + mSize;
    }
    //----------------- access -----------------
    T& at(int index) {
        rangeCheck(index);
        return mData[index];
    }

    T& at(int index) const {
        rangeCheck(index);
        return mData[index];
    }

    T& operator[](int index) {
        return mData[index];
    }

    T& operator[](int index) const {
        return mData[index];
    }

    //----------------- modifier -------------
    void push_back(const T& element) {
        insert(end(), element);
    }

    void pop_back() {
        mSize--;
    }

    iterator insert(iterator it, const T& element) {
        size_t pos = it - begin();
        ensureCapacity(mSize + 1);
        //      for(size_t i = mSize;i > pos;i--) {
        //        mData[i] = mData[i-1];
        //      }
        for (size_t i = pos; i < mSize; i++) {
            mData[i + 1] = mData[i];
        }
        mData[pos] = element;
        mSize++;
        return begin() + pos;
    }

    void erase(iterator it) {
        while ((it + 1) != end()) {
            *it = *(it + 1);
            it++;
        }
        mSize--;
    }

    void clear() {
        mSize = 0;
    }

    //-------------- extra (unlike STL) ------------------
    void insert_by_pos(size_t it, const T& element) {
        insert(begin() + it, element);
    }

    void erase_by_pos(int index) {
        erase(begin() + index);
    }

    void erase_by_value(const T& element) {
        int i = index_of(element);
        if (i != -1) erase_by_pos(i);
    }

    bool contains(const T& element) {
        return index_of(element) != -1;
    }

    int index_of(const T& element) {
        for (int i = 0; i < mSize; i++) {
            if (mData[i] == element) {
                return i;
            }
        }
        return -1;
    }

    bool valid_iterator(iterator it) const;
};

}  // namespace CP

#endif

// student.h

#ifndef __STUDENT_H_
#define __STUDENT_H_

template <typename T>
bool CP::vector<T>::valid_iterator(CP::vector<T>::iterator it) const {
    // write your code here
    const auto index = it - mData;
    return index >= 0 && index < mSize;
}

#endif

// main.cpp

#ifdef DEBUG
#include <iostream>
#include <stdexcept>
#include <vector>

bool test1() {
    CP::vector<int> v(10);
    auto it = v.begin();
    if (!(v.valid_iterator(v.end()) == false)) return false;
    return v.valid_iterator(it) == true;
}

bool test2() {
    CP::vector<int> v;
    auto it = v.begin();
    return v.valid_iterator(it) == false;
}

bool test3() {
    CP::vector<int> v(1), v2(1);
    auto it = v2.begin();
    if (!(v2.valid_iterator(it) == true)) return false;
    return v.valid_iterator(it) == false;
}

bool test4() {
    CP::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    auto it = v.begin() + 1;
    v.push_back(30);
    if (!(v.valid_iterator(v.end() - 1) == true)) return false;
    return v.valid_iterator(it) == false;
}

bool test5() {
    CP::vector<int> v(10);
    v.resize(3);
    auto it = v.begin() + 3;
    if (!(v.valid_iterator(v.begin()) == true)) return false;
    return v.valid_iterator(it) == false;
}

bool test6() {
    CP::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    if (!(v.valid_iterator(v.begin() + 1) == true)) return false;
    auto it = v.begin() + 1;
    v.pop_back();
    return v.valid_iterator(it) == false;
}

bool test7() {
    CP::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    if (!(v.valid_iterator(v.end()) == false)) return false;
    auto it = v.begin() + 1;
    v.pop_back();
    v.push_back(30);
    return v.valid_iterator(it) == true;
}

bool test8() {
    CP::vector<int> v(11);
    if (!(v.valid_iterator(v.end() + 1) == false)) return false;
    v.erase(v.begin() + 5);
    auto it = v.end();
    v.insert(v.begin() + 5, 10);
    return v.valid_iterator(it) == true;
}

bool test9() {
    CP::vector<int> v(10);
    auto it = v.end() - 1;
    if (!(v.valid_iterator(it) == true)) return false;
    v.insert(v.begin() + 5, 10);
    return v.valid_iterator(it) == false;
}

bool test10() {
    CP::vector<int> v(10);
    auto it = v.begin();
    if (!(v.valid_iterator(it + v.size()) == false)) return false;
    v.erase(v.begin());
    return v.valid_iterator(it) == true;
}

int main() {
    int i;
    std::cin >> i;
    switch (i) {
        case 1:
            std::cout << (test1() ? "OK " : "WRONG") << std::endl;
            break;
        case 2:
            std::cout << (test2() ? "OK " : "WRONG") << std::endl;
            break;
        case 3:
            std::cout << (test3() ? "OK " : "WRONG") << std::endl;
            break;
        case 4:
            std::cout << (test4() ? "OK " : "WRONG") << std::endl;
            break;
        case 5:
            std::cout << (test5() ? "OK " : "WRONG") << std::endl;
            break;
        case 6:
            std::cout << (test6() ? "OK " : "WRONG") << std::endl;
            break;
        case 7:
            std::cout << (test7() ? "OK " : "WRONG") << std::endl;
            break;
        case 8:
            std::cout << (test8() ? "OK " : "WRONG") << std::endl;
            break;
        case 9:
            std::cout << (test9() ? "OK " : "WRONG") << std::endl;
            break;
        case 10:
            std::cout << (test10() ? "OK " : "WRONG") << std::endl;
            break;
    }
}
#endif
