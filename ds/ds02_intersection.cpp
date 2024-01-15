#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool inSortedVector(std::vector<int>& v, int target) {
    auto lb = std::lower_bound(v.begin(), v.end(), target);

    if (lb == v.end()) return false;
    return *lb == target;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> A, B;
    int N, M;
    std::cin >> N >> M;

    for (int i = 0; i < N; i++) {
        int t;
        std::cin >> t;

        A.push_back(t);
    }

    for (int i = 0; i < M; i++) {
        int t;
        std::cin >> t;

        B.push_back(t);
    }

    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());

    for (std::vector<int>::size_type i = 0; i < A.size(); i++) {
        if (i > 0 && A[i] == A[i - 1]) continue;

        if (inSortedVector(B, A[i])) {
            std::cout << A[i] << " ";
        }
    }

    std::cout << "\n";
}
