#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, a;
    std::cin >> m >> a;

    std::vector<int> descendants;
    std::queue<int> currgen;

    currgen.push(a);

    while (!currgen.empty()) {
        const auto top = currgen.front();
        currgen.pop();

        if (top >= m) {
            continue;
        }

        descendants.push_back(top);

        currgen.push(2 * top + 1);
        currgen.push(2 * top + 2);
    }

    std::cout << descendants.size() << "\n";

    for (const auto d : descendants) {
        std::cout << d << " ";
    }

    std::cout << "\n";
}
