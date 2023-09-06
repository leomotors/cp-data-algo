#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, start;
    std::cin >> n >> m >> start;

    std::vector<std::pair<int, int>> income;

    for (int i = 0; i < n; i++) {
        int a, s;
        std::cin >> a >> s;
        income.push_back({a, s});
    }

    std::sort(income.begin(), income.end());

    std::vector<int> money;
    int rate = start;
    auto it = income.cbegin();
    money.push_back(start);
    for (int i = 1; i <= 100'069; i++) {
        if (it != income.cend() && it->first == i) {
            rate = it->second;
            it++;
        }

        money.push_back(money[i - 1] + rate);
    }

    for (int i = 0; i < m; i++) {
        int P, x;
        std::cin >> P >> x;

        const auto moneyAtYeet = money[x];

        if (moneyAtYeet >= P) {
            const auto ans =
                std::lower_bound(money.cbegin(), money.cbegin() + x, P) -
                money.cbegin();

            std::cout << ans << " ";
        } else {
            const auto ans = std::lower_bound(money.cbegin() + x + 1,
                                              money.cend(), P + moneyAtYeet) -
                             money.cbegin();

            std::cout << ans << " ";
        }
    }

    std::cout << "\n";
}
