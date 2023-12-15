// You may include library here

int _depth(node *n, int cum) {
    int height = cum;

    if (n->left_child != nullptr) {
        height = std::max(height, _depth(n->left_child, cum + 1));
    }

    if (n->right_sibling != nullptr) {
        height = std::max(height, _depth(n->right_sibling, cum));
    }

    return height;
}

int depth(node *n) {
    if (n == nullptr) {
        return -1;
    }

    return _depth(n, 0);
}
