#include <cmath>
#include <iostream>

int main() {
    int n;
    std::cin >> n;

    std::cout << static_cast<int>(std::pow(2, std::ceil(std::log2(n))) - n)
              << "\n";
}
