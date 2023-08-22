#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> N;
    for (int i = 0; i < n; i++) {
        int t;
        std::cin >> t;

        N.push_back(t);
    }

    std::sort(N.begin(), N.end());

    for (int i = 0; i < m; i++) {
        int P;
        std::cin >> P;

        auto low = std::lower_bound(N.begin(), N.end(), P - k);
        auto high = std::upper_bound(N.begin(), N.end(), P + k);

        std::cout << high - low << " ";
    }
}
