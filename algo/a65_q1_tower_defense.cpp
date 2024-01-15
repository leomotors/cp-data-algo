#include <algorithm>
#include <iostream>
#include <utility>

int main() {
    int n, m, k, w;
    std::cin >> n >> m >> k >> w;

    std::pair<int, int> monsters[m];

    for (int i = 0; i < m; i++) {
        std::cin >> monsters[i].first;
    }

    for (int i = 0; i < m; i++) {
        std::cin >> monsters[i].second;
    }

    std::sort(monsters, monsters + m);

    int t[k];
    for (int i = 0; i < k; i++) {
        std::cin >> t[i];
    }

    std::sort(t, t + k);

    for (int i = 0; i < k; i++) {
        int rangeMin = t[i] - w;
        int rangeMax = t[i] + w;

        for (int j = 0; j < m; j++) {
            if (monsters[j].first > rangeMax) {
                break;
            }

            if (monsters[j].first < rangeMin) {
                continue;
            }

            if (monsters[j].second > 0) {
                monsters[j].second--;
                break;
            }
        }
    }

    int total = 0;
    for (int i = 0; i < m; i++) {
        total += monsters[i].second;
    }

    std::cout << total << "\n";
}
