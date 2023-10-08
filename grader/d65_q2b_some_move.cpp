// vector-sm.h

#ifndef _CP_VECTOR_SM_INCLUDED_
#define _CP_VECTOR_SM_INCLUDED_

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

//#pragma once

namespace CP {

template <typename T>
class vector_some_move {
  protected:
    std::vector<std::vector<T>> mData;
    size_t mCap;
    size_t mSize;
    std::vector<int> aux;

    void expand(size_t capacity) {
        int additional_capacity = capacity - mCap;
        mData.push_back(std::vector<T>(additional_capacity));
        mCap = capacity;

        expand_hook();
    }

    void ensureCapacity(size_t capacity) {
        if (capacity > mCap) {
            expand(capacity);
        }
    }

  public:
    //-------------- constructor & copy operator ----------

    // copy constructor
    vector_some_move(const vector_some_move<T> &a) {
        mData = a.mData;
        mCap = a.mCap;
        mSize = a.mSize;
        aux = a.aux;
    }

    // default constructor
    vector_some_move() {
        mCap = 0;
        mSize = 0;
    }
    // constructor from vector
    vector_some_move(const std::vector<std::vector<T>> &t) {
        mData = t;
        for (size_t i = 0; i < mData.size(); ++i) {
            if (i == 0) {
                aux.push_back(mData[i].size());
            } else {
                aux.push_back(aux[i - 1] + mData[i].size());
            }
        }
        mCap = aux.back();
        mSize = aux.back();
    }

    // copy assignment operator using copy-and-swap idiom
    vector_some_move<T> &operator=(vector_some_move<T> other) {
        // other is copy-constructed which will be destruct at the end of this
        // scope we swap the content of this class to the other class and let it
        // be destructed
        using std::swap;
        swap(this->mSize, other.mSize);
        swap(this->mCap, other.mCap);
        swap(this->mData, other.mData);
        swap(this->aux, other.aux);
        return *this;
    }

    ~vector_some_move() {}

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
        // resize is guaranteed to be called with MORE THAN mCap
        if (n > mCap) {
            ensureCapacity(n);
            mSize = n;
        }
    }

    //----------------- access -----------------
    T &operator[](int idx) {
        int i = std::upper_bound(aux.begin(), aux.end(), idx) - aux.begin();
        if (i > 0) idx -= aux[i - 1];
        return mData[i][idx];
    }

    void expand_hook() {
        aux.push_back(mCap);
    }

    //----------------- modifier -------------
    void push_back(const T &element) {
        // since we guaranteed that vector is always full,
        // this will always add additional vector to mData
        // with just ONE additional member
        ensureCapacity(mSize + 1);

        // set the last one to be element
        mData.back().back() = element;
        mSize++;
    }

    void insert(int index, std::vector<T> &value);

    void debug() {
        std::cout << "--- debug ---\nmSize = " << mSize << " mCap = " << mCap
                  << std::endl;
        for (size_t i = 0; i < mData.size(); i++) {
            std::cout << "mData[" << i << "]: ";
            for (size_t j = 0; j < mData[i].size(); j++) {
                std::cout << mData[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "aux: ";
        for (auto &x : aux) std::cout << x << " ";
        std::cout << std::endl;
    }
};

}  // namespace CP

#endif

// student.h
#ifndef __STUDENT_H_
#define __STUDENT_H_

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void CP::vector_some_move<T>::insert(int index, std::vector<T> &value) {
    int i = std::upper_bound(aux.begin(), aux.end(), index) - aux.begin();
    int idx = i > 0 ? index -= aux[i - 1] : index;

    mSize += value.size();
    mCap += value.size();
    std::vector<T> newVector;

    // Update aux
    aux.push_back(aux.back() + value.size());
    for (int k = aux.size() - 2; k > i; k--) {
        aux[k] = aux[k + 1] - (aux[k] - aux[k - 1]);
    }

    auto &mDataI = mData[i];

    // Get data range
    std::vector<T> newRange(value.cbegin(), value.cend());
    for (int k = idx; k < mDataI.size(); k++) {
        newRange.push_back(mDataI[k]);
    }

    // Apply data range to mData[i]

    for (int k = idx; k < mDataI.size(); k++) {
        mDataI[k] = newRange[k - idx];
    }

    // Apply data range to newVector
    for (int k = mDataI.size() - idx; k < newRange.size(); k++) {
        newVector.push_back(newRange[k]);
    }

    mData.insert(mData.cbegin() + i + 1, newVector);
}

#endif

// main.cpp
#ifdef DEBUG
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main() {
    CP::vector_some_move<int> v;
    int n, m, pos;  // n   - Amount of time to be resized
                    // m   - Amount of element to be inserted
                    // pos - postion of the vector to insert to
    cin >> n >> m >> pos;
    for (int i = 0; i < n; ++i) {
        int sz;
        cin >> sz;
        v.resize(v.size() + sz);  // Expand v with sz more element
    }
    for (int i = 0; i < v.size(); ++i) {
        cin >> v[i];  // Each element of the vector_some_move (v)
    }
    std::vector<int> to_be_insert(m);  // The values to be inserted
    for (int i = 0; i < m; ++i) {
        cin >> to_be_insert[i];
    }
    cout << "--- BEFORE INSERT ---" << endl;
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    v.insert(pos, to_be_insert);  // Inserting values
    cout << "--- AFTER INSERT ---" << endl;
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

#endif