#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> times;

    for (int i = 0; i < N; i++) {
        int t;
        std::cin >> t;
        times.push_back(t);
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    for (int i = 0; i < std::min(N, M); i++) {
        pq.push({times[i], i});
        std::cout << "0\n";
    }

    for (int i = N; i < M; i++) {
        const auto [curr, pos] = pq.top();
        pq.pop();
        std::cout << curr << "\n";
        pq.push({curr + times[pos], pos});
    }
}
