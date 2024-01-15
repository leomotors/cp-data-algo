#include <iostream>
#include <map>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::map<std::string, int> hist;

    for (int i = 0; i < N; i++) {
        std::string key;
        std::cin >> key;

        hist[key]++;
    }

    for (const auto& [key, value] : hist) {
        if (value <= 1) continue;

        std::cout << key << " " << value << "\n";
    }
}