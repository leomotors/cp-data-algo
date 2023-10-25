#pragma region list.h
#ifndef _CP_LIST_INCLUDED_
#define _CP_LIST_INCLUDED_

#include <iostream>
#include <stdexcept>
// #pragma once

namespace CP {

template <typename T>
class list {
  protected:
    class node {
        friend class list;

      public:
        T data;
        node* prev;
        node* next;

        node() : data(T()), prev(this), next(this) {}

        node(const T& data, node* prev, node* next)
            : data(T(data)), prev(prev), next(next) {}
    };

    class list_iterator {
        friend class list;

      protected:
        node* ptr;

      public:
        list_iterator() : ptr(NULL) {}

        list_iterator(node* a) : ptr(a) {}

        list_iterator& operator++() {
            ptr = ptr->next;
            return (*this);
        }

        list_iterator& operator--() {
            ptr = ptr->prev;
            return (*this);
        }

        list_iterator operator++(int) {
            list_iterator tmp(*this);
            operator++();
            return tmp;
        }
        list_iterator operator--(int) {
            list_iterator tmp(*this);
            operator--();
            return tmp;
        }

        T& operator*() {
            return ptr->data;
        }
        T* operator->() {
            return &(ptr->data);
        }
        bool operator==(const list_iterator& other) const {
            return other.ptr == ptr;
        }
        bool operator!=(const list_iterator& other) const {
            return other.ptr != ptr;
        }
    };

  public:
    typedef list_iterator iterator;

  protected:
    node* mHeader;  // pointer to a header node
    size_t mSize;

  public:
    //-------------- constructor & copy operator ----------

    // copy constructor
    list(const list<T>& a) : mHeader(new node()), mSize(0) {
        for (auto it = a.begin(); it != a.end(); it++) {
            push_back(*it);
        }
    }

    // default constructor
    list() : mHeader(new node()), mSize(0) {}

    // copy assignment operator using copy-and-swap idiom
    list<T>& operator=(list<T> other) {
        // other is copy-constructed which will be destruct at the end of this
        // scope we swap the content of this class to the other class and let it
        // be descructed
        using std::swap;
        swap(this->mHeader, other.mHeader);
        swap(this->mSize, other.mSize);
        return *this;
    }

    ~list() {
        clear();
        delete mHeader;
    }

    //------------- capacity function -------------------
    bool empty() const {
        return mSize == 0;
    }

    size_t size() const {
        return mSize;
    }

    //----------------- iterator ---------------
    iterator begin() {
        return iterator(mHeader->next);
    }

    iterator end() {
        return iterator(mHeader);
    }

    iterator begin() const {
        return iterator(mHeader->next);
    }

    iterator end() const {
        return iterator(mHeader);
    }
    //----------------- access -----------------
    T& front() {
        return mHeader->next->data;
    }

    T& back() {
        return mHeader->prev->data;
    }

    //----------------- modifier -------------
    void push_back(const T& element) {
        insert(end(), element);
    }

    void push_front(const T& element) {
        insert(begin(), element);
    }

    void pop_back() {
        erase(iterator(mHeader->prev));
    }

    void pop_front() {
        erase(begin());
    }

    iterator insert(iterator it, const T& element) {
        node* n = new node(element, it.ptr->prev, it.ptr);
        it.ptr->prev->next = n;
        it.ptr->prev = n;
        mSize++;
        return iterator(n);
    }

    iterator erase(iterator it) {
        iterator tmp(it.ptr->next);
        it.ptr->prev->next = it.ptr->next;
        it.ptr->next->prev = it.ptr->prev;
        delete it.ptr;
        mSize--;
        return tmp;
    }

    void clear() {
        while (mSize > 0) erase(begin());
    }

    void print() {
        std::cout << "Size = " << mSize << "\n";
        std::cout << "From FRONT to BACK: ";
        for (auto it = begin(); it != end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl << "From BACK to FRONT: ";
        auto it = end();
        while (it != begin()) {
            --it;
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

    void merge(list<list<T>>& ls);
};

}  // namespace CP

#endif
#pragma endregion list.h

#pragma region student.h
#ifndef __STUDENT_H_
#define __STUDENT_H_
#include <algorithm>

template <typename T>
void CP::list<T>::merge(CP::list<CP::list<T>>& ls) {
    for (auto& l : ls) {
        this->mHeader->prev->next = l.mHeader->next;
        l.mHeader->next->prev = this->mHeader->prev;
        this->mHeader->prev = l.mHeader->prev;
        this->mHeader->prev->next = this->mHeader;

        this->mSize += l.mSize;

        l.mHeader->prev = l.mHeader;
        l.mHeader->next = l.mHeader;
        l.mSize = 0;
    }
}

#endif
#pragma endregion student.h

#pragma region main.cpp
#ifdef DEBUG

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m;
    cin >> n >> m;

    // read the first list
    CP::list<int> l;
    for (int j = 0; j < n; j++) {
        int tmp;
        cin >> tmp;
        l.push_back(tmp);
    }

    // read m lists
    CP::list<CP::list<int>> ls;
    for (int i = 0; i < m; i++) {
        ls.push_back(CP::list<int>());
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int tmp;
            cin >> tmp;
            ls.back().push_back(tmp);
        }
    }

    l.merge(ls);
    l.print();
}

#endif
#pragma endregion main.cpp
