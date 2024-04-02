#include <initializer_list>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

int north[1000][1000], south[1000][1000];
std::vector<std::pair<int, int>> worms;
std::map<std::pair<int, int>, int> wormAnswer;

int R, C, K;

int bfs(auto target, const std::pair<int, int> start = {1, 1},
        int setValue = 0) {
    std::set<std::pair<int, int>> nVisited;
    std::queue<std::pair<int, int>> nQueue;
    nQueue.push(start);
    int score = 0;

    while (!nQueue.empty()) {
        const auto curr = nQueue.front();
        nQueue.pop();

        if (nVisited.find(curr) != nVisited.end()) {
            continue;
        }

        nVisited.insert(curr);
        score++;
        target[curr.first][curr.second] = setValue;

        const std::initializer_list<std::pair<int, int>> diff = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (const auto &[dx, dy] : diff) {
            std::pair<int, int> next =
                std::make_pair(curr.first + dx, curr.second + dy);
            if (target[next.first][next.second] > 0 || next.first < 1 ||
                next.first > R || next.second < 1 || next.second > C) {
                continue;
            }

            if (nVisited.find(next) == nVisited.end()) {
                nQueue.push(next);
            }
        }
    }

    return score;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> R >> C >> K;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            std::cin >> north[i][j];
        }
    }

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            std::cin >> south[i][j];
        }
    }

    for (int i = 0; i < K; i++) {
        int wr, wc;
        std::cin >> wr >> wc;
        worms.push_back({wr, wc});
    }

    // Explore North
    int northScore = bfs(north, {1, 1}, -1);

    // Explore South
    int index = 1;
    int bestSouthScore = 0;
    for (const auto &[x, y] : worms) {
        index++;

        if (north[x][y] != -1 || south[x][y] != 0) {
            // Already Explore
            continue;
        }

        int southScore = bfs(south, {x, y}, -index);
        bestSouthScore = std::max(bestSouthScore, southScore);
    }

    std::cout << northScore + bestSouthScore << "\n";
}
