#include <cmath>
#include <iostream>
#include <vector>

std::vector<int> dna;
int n, k, len;

bool isVirus(int begin, int end, bool reverse) {
    int level = end - begin;

    if (level == 2) {
        if (!reverse) {
            return dna[begin] == 0 && dna[begin + 1] == 1;
        } else {
            return dna[begin + 1] == 0 && dna[begin] == 1;
        }
    }

    int mid = (begin + end) / 2;

    if (!reverse) {
        return (isVirus(begin, mid, false) || isVirus(begin, mid, true)) &&
               isVirus(mid, end, false);
    } else {
        return (isVirus(mid, end, false) || isVirus(mid, end, true)) &&
               isVirus(begin, mid, true);
    }
}

void solve() {
    for (int i = 0; i < len; i++) {
        std::cin >> dna[i];
    }

    std::cout << (isVirus(0, len, false) ? "yes" : "no") << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
    len = std::pow(2, k);

    dna = std::vector<int>(len);

    while (n--) {
        solve();
    }
}
