#include <iostream>
#include <set>
#include <utility>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::set<std::pair<int, int>> manga;

    for (int i = 0; i < n; i++) {
        int y, mo;
        std::cin >> y >> mo;
        manga.insert({y, mo});
    }

    for (int i = 0; i < m; i++) {
        int y, mo;
        std::cin >> y >> mo;

        auto res = manga.lower_bound({y, mo});

        if (res != manga.end() && *res == std::make_pair(y, mo)) {
            std::cout << "0 0 ";
            continue;
        }

        if (res == manga.begin()) {
            std::cout << "-1 -1 ";
            continue;
        }

        res--;

        std::cout << res->first << " " << res->second << " ";
    }
}
