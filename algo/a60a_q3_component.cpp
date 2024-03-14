#include <iostream>
#include <queue>
#include <set>
#include <vector>

std::set<int> seen;
std::vector<std::vector<int>> adj;
int v, e;

void dfs(int s) {
    std::queue<int> bfs;
    bfs.push(s);

    while (!bfs.empty()) {
        const auto front = bfs.front();
        bfs.pop();

        if (seen.find(front) != seen.end()) {
            continue;
        }

        seen.insert(front);

        for (const auto next : adj[front]) {
            bfs.push(next);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> v >> e;

    adj = std::vector<std::vector<int>>(v + 1);

    for (int i = 0; i < e; i++) {
        int a, b;
        std::cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int ans = 0;

    for (int i = 1; i <= v; i++) {
        if (seen.find(i) != seen.end()) {
            continue;
        }

        ans += 1;
        dfs(i);
    }

    std::cout << ans << "\n";
}