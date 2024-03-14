#include <iostream>

int n;
int maki[5005];

int mcache[5005][5005];

int gean_cache(int, int);

int gean(int s, int e) {
    if (e - s == 1) {
        return std::max(maki[s], maki[e]);
    }

    int r1 = std::max(maki[s], maki[s + 1]) + gean_cache(s + 2, e);
    int r2 = gean_cache(s, e - 2) + std::max(maki[e - 1], maki[e]);
    int r3 = std::max(maki[s], maki[e]) + gean_cache(s + 1, e - 1);

    return std::max(std::max(r1, r2), r3);
}

int gean_cache(int s, int e) {
    if (mcache[s][e]) {
        return mcache[s][e];
    }

    mcache[s][e] = gean(s, e);
    return mcache[s][e];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> maki[i];

        for (int j = 0; j < n; j++) {
            mcache[i][j] = 0;
        }
    }

    std::cout << gean_cache(0, n - 1) << "\n";
}
