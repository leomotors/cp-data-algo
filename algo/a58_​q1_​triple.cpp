#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a;

    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        a.push_back(x);
    }

    for (int _m = 0; _m < m; _m++) {
        int query;
        std::cin >> query;

        bool found = false;

        for (int i = 0; i < n; i++) {
            int x = a[i];

            int target = query - x;

            int ub = std::upper_bound(a.cbegin() + i + 1, a.cend(),
                                      target - target / 2) -
                     a.cbegin();

            for (int j = i + 1; j < ub; j++) {
                int y = a[j];
                int z = target - y;

                if (std::binary_search(a.cbegin() + j + 1, a.cend(), z)) {
                    found = true;
                    break;
                }
            }

            if (found) {
                break;
            }
        }

        std::cout << (found ? "YES" : "NO") << "\n";
    }
}