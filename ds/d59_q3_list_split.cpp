#pragma region list.h
#ifndef _CP_LIST_INCLUDED_
#define _CP_LIST_INCLUDED_

#include <iostream>
#include <stdexcept>

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
        bool operator==(const list_iterator& other) {
            return other.ptr == ptr;
        }
        bool operator!=(const list_iterator& other) {
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
        for (auto& x : *this) {
            push_back(x);
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
        std::cout << " Size = " << mSize << std::endl;
        std::cout << " Header address = " << (mHeader)
                  << " (prev = " << mHeader->prev << " next = " << mHeader->next
                  << ")" << std::endl;
        int i = 0;
        iterator before;
        for (iterator it = begin(); it != end(); before = it, it++, i++) {
            std::cout << "Node " << i << ": " << *it;
            std::cout << " (prev = " << it.ptr->prev << ", I'm at " << it.ptr
                      << ", next = " << it.ptr->next << ")" << std::endl;
        }
    }

    CP::list<T> split(iterator it, size_t pos);
};

}  // namespace CP
#endif
#pragma endregion list.h

#pragma region student.h
#ifndef __STUDENT_H_
#define __STUDENT_H_

template <typename T>
CP::list<T> CP::list<T>::split(iterator it, size_t pos) {
    // write your code here
    CP::list<T> result;

    if (it == this->end()) {
        return result;
    }

    if (it == this->begin()) {
        result.mHeader = this->mHeader;
        result.mSize = this->mSize;

        this->mHeader = new node();
        this->mSize = 0;

        return result;
    }

    // Config mHeader of new list
    result.mHeader = new node(T(), this->mHeader->prev, it.ptr);
    result.mHeader->prev->next = result.mHeader;
    result.mSize = this->mSize - pos;
    const auto endOfSplited = it.ptr->prev;
    it.ptr->prev = result.mHeader;

    // Config mHeader of original list
    this->mSize = pos;
    this->mHeader->prev = endOfSplited;
    endOfSplited->next = this->mHeader;

    return result;
}

#endif
#pragma endregion student.h

#pragma region main.cpp
#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <stdexcept>
#include <vector>

bool check(CP::list<int>& l, CP::list<int>& check) {
    bool ok = true;
    // report result
    if (check.size() != l.size()) {
        printf("Size is wrong\n");
        ok = false;
    }

    // check "next" pointer
    CP::list<int>::iterator it1, it2;
    it1 = l.begin();
    it2 = check.begin();
    for (size_t i = 0; i < check.size(); i++) {
        if (*it1 != *it2) {
            printf("wrong data\n");
            ok = false;
        }
        it1++;
        it2++;
    }
    if (it1 != l.end()) {
        printf("wrong end() for l\n");
        ok = false;
    }

    // check "prev" pointer
    it1 = l.end();
    it2 = check.end();
    for (size_t i = 0; i < check.size(); i++) {
        it1--;
        it2--;
        if (*it1 != *it2) {
            printf("wrong data\n");
            ok = false;
        }
    }
    if (it1 != l.begin()) {
        printf("wrong begin() for l\n");
        ok = false;
    }
    return ok;
}

int main() {
    int vsize, cutpos;
    std::cin >> vsize >> cutpos;

    std::vector<int> v;
    for (int i = 1; i <= vsize; i++) {
        v.push_back(i);
    }

    size_t pos = cutpos;

    // add value from v to l
    CP::list<int> l1;
    for (auto x : v) l1.push_back(x);

    // create it and pos
    auto it = l1.begin();
    for (size_t i = 0; i < pos; i++) {
        it++;
    }

    // call the split
    CP::list<int> l2;
    l2 = l1.split(it, pos);

    printf("-------- the remaining list ---------\n");
    l1.print();
    printf("-------- the split list ---------\n");
    l2.print();

    // check
    // create the correct result in O(N)
    CP::list<int> check1, check2;
    for (size_t i = 0; i < v.size(); i++) {
        if (i < pos) check1.push_back(v[i]);
        if (i >= pos) check2.push_back(v[i]);
    }

    printf("checking l1 (the original list)\n");
    bool b1 = check(l1, check1);
    printf("checking l2 (the returned list)\n");
    bool b2 = check(l2, check2);

    if (b1 && b2) {
        printf("CONCLUSION: correct\n");
    } else {
        printf("CONCLUSION: wrong\n");
    }

    return 0;
}
#endif
#pragma endregion main.cpp
