#include <initializer_list>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

int weight[500][500];
int dist[500][500];

const std::vector<std::pair<int, int>> nextOdd = {{-1, -1}, {-1, 0}, {-1, 1},
                                                  {0, -1},  {1, 0},  {0, 1}};
const std::vector<std::pair<int, int>> nextEven = {{0, -1}, {-1, 0}, {0, 1},
                                                   {1, -1}, {1, 0},  {1, 1}};

const std::vector<std::pair<int, int>> getNext(int col) {
    if (col % 2) {
        return nextOdd;
    } else {
        return nextEven;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int R, C, srcx, srcy, destx, desty;
    std::cin >> R >> C >> srcy >> srcx >> desty >> destx;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            std::cin >> weight[i][j];
            dist[i][j] = INT32_MAX;
        }
    }

    std::set<std::pair<int, int>> seen;
    std::priority_queue<std::pair<int, std::pair<int, int>>> next;
    dist[srcx][srcy] = weight[srcx][srcy];
    next.push({-weight[srcx][srcy], {srcx, srcy}});

    while (!next.empty()) {
        const auto [w, top] = next.top();
        next.pop();

        if (seen.find(top) != seen.end()) {
            continue;
        }

        seen.insert(top);

        int loopntimes = 0;
        for (const auto &[dx, dy] : getNext(top.second)) {
            loopntimes++;
            int nx = top.first + dx;
            int ny = top.second + dy;

            dist[nx][ny] = std::min(dist[nx][ny], -w + weight[nx][ny]);

            if (nx >= 1 && nx <= R && ny >= 1 && ny <= C &&
                seen.find({nx, ny}) == seen.end()) {
                next.push({-dist[nx][ny], {nx, ny}});
            }
        }
    }

    std::cout << dist[destx][desty] << "\n";
}
