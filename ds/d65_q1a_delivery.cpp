#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::queue<int> foodGoldfish, dotMan;
    std::vector<int> salesGoal, salesQuickSum;
    salesQuickSum.push_back(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int p;
        std::cin >> p;
        salesGoal.push_back(p);
    }

    for (int i = 0; i < n; i++) {
        int t;
        std::cin >> t;

        if (t == 1) {
            int shop, price;
            std::cin >> shop >> price;

            (shop == 1 ? foodGoldfish : dotMan).push(price);
        } else {
            int f = foodGoldfish.empty() ? INT32_MAX : foodGoldfish.front();
            int d = dotMan.empty() ? INT32_MAX : dotMan.front();

            if (f <= d) {
                foodGoldfish.pop();
                salesQuickSum.push_back(salesQuickSum.back() + f);
            } else {
                dotMan.pop();
                salesQuickSum.push_back(salesQuickSum.back() + d);
            }
        }
    }

    for (const auto p : salesGoal) {
        int pos =
            std::lower_bound(salesQuickSum.cbegin(), salesQuickSum.cend(), p) -
            salesQuickSum.cbegin();

        std::cout << (pos >= salesQuickSum.size() ? -1 : pos) << " ";
    }
}
