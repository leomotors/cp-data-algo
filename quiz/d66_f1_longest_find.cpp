#include <iostream>

uint8_t status[2005];
int oa[2005];

int insert(int n, int b, bool skipAction = false) {
    int h0 = b % n;
    int j = 0;

    while (true) {
        int target = (h0 + j * j) % n;

        j++;

        if (status[target] == 2) {
            continue;
        } else {
            if (!skipAction) {
                status[target] = 2;
                oa[target] = b;
            }
            break;
        }
    }

    return j;
}

int erase(int n, int b, bool skipAction = false) {
    int h0 = b % n;
    int j = 0;

    while (true) {
        int target = (h0 + j * j) % n;
        j++;

        if (status[target] == 0) {
            break;
        } else if (status[target] == 2 && oa[target] == b) {
            if (!skipAction) {
                status[target] = 1;
            }

            break;
        }
    }

    return j;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; i++) {
        status[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;

        if (a == 1) {
            insert(n, b);
        } else {
            erase(n, b);
        }
    }

    int maxA = 0;
    int maxB = 0;

    for (int i = 0; i < n; i++) {
        maxA = std::max(maxA, insert(n, 69420 + i, true));
        maxB = std::max(maxB, erase(n, 69420 + i, true));
    }

    std::cout << maxA << ' ' << maxB << '\n';
}
