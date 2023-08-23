#include <iostream>
#include <set>

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    std::multiset<int> deck;

    for (int i = 0; i < n; i++) {
        int p;
        std::cin >> p;
        deck.insert(p);
    }

    for (int round = 1; round <= m; round++) {
        int enemyCards;
        std::cin >> enemyCards;

        for (int i = 0; i < enemyCards; i++) {
            int enemyPower;
            std::cin >> enemyPower;

            auto defendCard = deck.upper_bound(enemyPower);

            if (defendCard == deck.end()) {
                // :skull:
                std::cout << round << "\n";
                return 0;
            }

            deck.erase(defendCard);
        }
    }

    std::cout << m + 1 << "\n";
}
