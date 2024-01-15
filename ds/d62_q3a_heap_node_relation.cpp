#include <iostream>
#include <string>

int n, m;

const char* notRelated = "a and b are not related\n";

inline int findParent(const int child) {
    return (child - 1) / 2;
}

bool isAncestorOf(const int parent, int child) {
    while (child > parent) {
        child = findParent(child);
    }

    return child == parent;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;

        if (a == b) {
            std::cout << "a and b are the same node\n";
        } else if (a < b) {
            std::cout << (isAncestorOf(a, b) ? "a is an ancestor of b\n"
                                             : notRelated);
        } else {
            std::cout << (isAncestorOf(b, a) ? "b is an ancestor of a\n"
                                             : notRelated);
        }
    }
}
