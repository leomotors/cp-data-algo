#include <iomanip>
#include <iostream>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(2);

    int n;
    std::cin >> n;

    std::map<std::string, int> courseReviewScore;
    std::map<std::string, int> courseReviewCount;
    std::map<std::string, int> profReviewScore;
    std::map<std::string, int> profReviewCount;

    for (int i = 0; i < n; i++) {
        std::string S, T;
        int R;

        std::cin >> S >> T >> R;
        courseReviewScore[S] += R;
        courseReviewCount[S] += 1;
        profReviewScore[T] += R;
        profReviewCount[T] += 1;
    }

    for (const auto& [course, score] : courseReviewScore) {
        std::cout << course << " "
                  << static_cast<double>(score) / courseReviewCount[course]
                  << "\n";
    }

    for (const auto& [prof, score] : profReviewScore) {
        std::cout << prof << " "
                  << static_cast<double>(score) / profReviewCount[prof] << "\n";
    }
}
