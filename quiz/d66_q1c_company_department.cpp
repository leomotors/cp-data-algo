#include <iostream>
#include <map>
#include <set>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::map<std::string, std::set<std::string>> dep;
    std::map<std::string, std::string> person;

    for (int i = 0; i < N; i++) {
        std::string n, d;
        std::cin >> n >> d;
        dep[d].insert(n);
        person[n] = d;
    }

    for (int i = 0; i < M; i++) {
        int t;
        std::string p1, p2;
        std::cin >> t >> p1 >> p2;

        if (t == 1) {
            auto oldDep = person[p1];
            dep[oldDep].erase(p1);
            dep[p2].insert(p1);
            person[p1] = p2;
        } else if (t == 2) {
            auto &rip = dep[p1];

            for (auto &p : rip) {
                dep[p2].insert(p);
                person[p] = p2;
            }

            dep.erase(p1);
        }
    }

    for (const auto &[d, p] : dep) {
        std::cout << d << ":";

        for (const auto &n : p) {
            std::cout << " " << n;
        }
        std::cout << "\n";
    }
}