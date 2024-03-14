#include <iostream>
#include <queue>
#include <set>
#include <vector>

std::set<int> seen;
std::vector<std::vector<int>> adj;
int v, e;

int isConnectedLine(int s) {
    bool isLine = true;
    bool hasEdge = adj[s].size() > 0;
    int oneDegCount = 0;

    std::queue<int> bfs;
    bfs.push(s);

    while (!bfs.empty()) {
        const auto front = bfs.front();
        bfs.pop();

        if (seen.find(front) != seen.end()) {
            continue;
        }

        seen.insert(front);

        const auto deg = adj[front].size();

        if (deg > 2) {
            isLine = false;
        }

        if (deg == 1) {
            oneDegCount += 1;
        }

        for (const auto next : adj[front]) {
            bfs.push(next);
        }
    }

    if (hasEdge && oneDegCount != 2) {
        isLine = false;
    }

    return isLine ? 1 : 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> v >> e;

    adj = std::vector<std::vector<int>>(v);

    for (int i = 0; i < e; i++) {
        int a, b;
        std::cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int ans = 0;

    for (int i = 0; i < v; i++) {
        if (seen.find(i) != seen.end()) {
            continue;
        }

        ans += isConnectedLine(i);
    }

    std::cout << ans << "\n";
}