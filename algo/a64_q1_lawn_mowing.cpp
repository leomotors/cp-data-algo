#include <iostream>

int64_t a[500005];
int64_t qs[500005];

int64_t n, m, k;

inline int64_t getQs(int l, int r) {
    return qs[r] - (l > 0 ? qs[l - 1] : 0);
}

inline int64_t calcPrice(int l, int r) {
    return getQs(l, r) + (r - l + 1) * k;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    qs[0] = a[0];
    for (int i = 1; i < n; i++) {
        qs[i] = qs[i - 1] + a[i];
    }

    for (int q = 0; q < m; q++) {
        int lborder;
        int64_t budget;
        std::cin >> lborder >> budget;

        if (calcPrice(lborder, lborder) > budget) {
            std::cout << "0\n";
            continue;
        }

        int l = lborder, r = n - 1;

        while (l < r) {
            const int mid = r - (r - l) / 2;

            const int64_t price = calcPrice(lborder, mid);
            if (price > budget) {
                r = mid - 1;
            } else {
                l = mid;
            }
        }

        int64_t ans = getQs(lborder, l);
        std::cout << ans << "\n";
    }
}
