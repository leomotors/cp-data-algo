#include <iostream>
#include <string>

auto paddingZero(int n) {
    if (n < 10) {
        return std::string("0") + std::to_string(n);
    } else {
        return std::to_string(n);
    }
}

int main() {
    int H, M, X;
    std::cin >> H >> M >> X;

    M += X;
    H += M / 60;
    M %= 60;
    H %= 24;

    std::cout << paddingZero(H) << " " << paddingZero(M) << std::endl;
}
