#ifndef __STUDENT_H_
#define __STUDENT_H_

#include "map_bst.h"

template <typename KeyT, typename MappedT, typename CompareT>
void CP::map_bst<KeyT, MappedT, CompareT>::my_recur(node* n, int level,
                                                    int tmp) {
    // you MAY need to use this function
    if (n == nullptr) return;

    my_recur(n->left, level, tmp + 1);
    my_recur(n->right, level, tmp + 1);

    if (tmp > level) {
        auto par = n->parent;

        if (par) {
            if (par->left == n) {
                par->left = nullptr;
            } else {
                par->right = nullptr;
            }
        } else {
            mRoot = nullptr;
        }

        delete n;
        mSize--;
    }
}

template <typename KeyT, typename MappedT, typename CompareT>
void CP::map_bst<KeyT, MappedT, CompareT>::trim(int depth) {
    my_recur(mRoot, depth, 0);
}

#endif
