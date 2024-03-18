#include <initializer_list>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <utility>

const std::initializer_list<std::pair<int, int>> diff = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int R, C;
    std::cin >> R >> C;

    char map[R + 3][C + 3];

    for (int i = 1; i <= R; i++) {
        std::cin >> (map[i] + 1);
    }

    std::queue<std::tuple<int, int, int>> bfs;
    std::set<std::pair<int, int>> seen;
    bfs.push({1, 1, 0});

    while (!bfs.empty()) {
        const auto& [r, c, dist] = bfs.front();
        bfs.pop();

        if (r < 1 || c < 1 || r > R || c > C || map[r][c] == '#') {
            continue;
        }

        if (r == R && c == C) {
            std::cout << dist << "\n";
            return 0;
        }

        if (seen.find({r, c}) != seen.end()) {
            continue;
        }

        seen.insert({r, c});

        for (const auto& [dx, dy] : diff) {
            bfs.push({r + dx, c + dy, dist + 1});
        }
    }

    std::cout << "-1\n";
}
