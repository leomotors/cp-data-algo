#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> speed;
    std::vector<int> timestamp;
    speed.push_back(k);
    timestamp.push_back(0);

    std::vector<std::pair<int, int>> brakesInput;

    for (int i = 0; i < n; i++) {
        int t, d;
        std::cin >> t >> d;

        brakesInput.push_back({t, d});
    }

    std::sort(brakesInput.begin(), brakesInput.end());

    for (const auto& [t, d] : brakesInput) {
        speed.push_back(std::max(0, speed.back() - d));
        timestamp.push_back(t);

        if (speed.back() == 0) {
            break;
        }
    }

    for (int i = 0; i < m; i++) {
        int a, q;
        std::cin >> a >> q;

        if (a == 1) {
            auto loc =
                std::upper_bound(timestamp.cbegin(), timestamp.cend(), q) -
                timestamp.cbegin() - 1;
            std::cout << speed[loc] << "\n";
        } else {
            auto loc = std::lower_bound(speed.crbegin(), speed.crend(), q) -
                       speed.crbegin() - 1;

            loc = speed.size() - loc - 1;

            std::cout << timestamp[loc] << "\n";
        }
    }
}
