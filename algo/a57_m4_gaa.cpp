#include <algorithm>
#include <iostream>

int level[30];

bool check_answer(int N, int lvl) {
    if (lvl == 0) {
        return N == 1;
    }

    if (N <= level[lvl - 1]) {
        return check_answer(N, lvl - 1);
    }

    if (N <= level[lvl - 1] + lvl + 3) {
        return N == level[lvl - 1] + 1;
    }

    return check_answer(N - level[lvl - 1] - lvl - 3, lvl - 1);
}

int main() {
    int N;
    std::cin >> N;

    level[0] = 3;
    for (int i = 1; i < 29; i++) {
        level[i] = 2 * level[i - 1] + i + 3;
    }

    auto lvl = std::lower_bound(level, level + 29, N) - level;

    std::cout << (check_answer(N, lvl) ? "g" : "a") << "\n";
}
