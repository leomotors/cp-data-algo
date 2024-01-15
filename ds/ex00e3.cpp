#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<bool> seen(100002, false);

    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        int t;
        std::cin >> t;

        if (t < 0 || t > N) {
            std::cout << "NO\n";
            return 0;
        }

        if (seen[t]) {
            std::cout << "NO\n";
            return 0;
        }

        seen[t] = true;
    }

    std::cout << "YES\n";
}
