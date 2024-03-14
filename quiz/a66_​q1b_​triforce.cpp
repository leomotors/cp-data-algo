#include <iostream>

int tf[300][300];

int tfType(int rs, int re, int cs, int ce) {
    if (re - rs == 1) {
        return tf[rs][cs];
    }

    int rm = (rs + re) / 2;
    int cm = (cs + ce) / 2;

    for (int i = rm; i < re; i++) {
        for (int j = cm; j < ce; j++) {
            if (tf[i][j]) {
                return 0;
            }
        }
    }

    int tlT = tfType(rs, rm, cs, cm);
    int trT = tfType(rs, rm, cm, ce);
    int blT = tfType(rm, re, cs, cm);

    if (!tlT || !trT || !blT) {
        return 0;
    }

    if (tlT == trT) {
        return tlT;
    }

    if (tlT == blT) {
        return tlT;
    }

    if (trT == blT) {
        return trT;
    }

    return 0;
}

void run() {
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> tf[i][j];
        }
    }

    std::cout << tfType(0, n, 0, n) << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int i = 3;
    while (i--) {
        run();
    }
}
