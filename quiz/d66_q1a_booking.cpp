#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::map<std::string, bool> ticketAvailable;

    int N, M;
    std::cin >> N >> M;

    for (int i = 0; i < N; i++) {
        std::string flight, seat;
        std::cin >> flight >> seat;

        ticketAvailable[flight + "_" + seat] = true;
    }

    for (int i = 0; i < M; i++) {
        int K;
        std::cin >> K;

        std::vector<std::map<std::string, bool>::iterator> payload;
        bool isAvailable = true;

        for (int j = 0; j < K; j++) {
            std::string flight, seat;
            std::cin >> flight >> seat;

            if (!isAvailable) continue;

            auto key = flight + "_" + seat;
            const auto it = ticketAvailable.find(key);

            payload.push_back(it);

            isAvailable =
                (it != ticketAvailable.end() && it->second) && isAvailable;
        }

        if (isAvailable) {
            for (auto& it : payload) {
                it->second = false;
            }
        }

        std::cout << (isAvailable ? "YES\n" : "NO\n");
    }
}
