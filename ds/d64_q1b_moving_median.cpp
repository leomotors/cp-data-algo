#include <iostream>
#include <set>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, w;
    std::cin >> n >> w;

    int a[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::multiset<int> low, high, initial;
    int median;

    for (int i = 0; i <= w; i++) {
        initial.insert(a[i]);
    }

    auto it = initial.cbegin();
    for (int i = 0; i < w / 2; i++) {
        low.insert(*(it++));
    }
    median = *(it++);
    for (int i = 0; i < w / 2; i++) {
        high.insert(*(it++));
    }

    std::cout << median << " ";

    for (int i = 1; i < n - w; i++) {
        const int A = a[i - 1];
        const int B = a[i + w];

        // Remove
        if (A < median) {
            low.erase(low.find(A));
        } else if (A > median) {
            high.erase(high.find(A));
        } else {
            median = *high.begin();
            high.erase(high.begin());
        }

        // Add
        if (B < median) {
            low.insert(B);
        } else {
            high.insert(B);
        }

        // Balance
        if (low.size() < high.size()) {
            low.insert(median);
            median = *high.begin();
            high.erase(high.begin());
        } else if (low.size() > high.size()) {
            high.insert(median);
            median = *low.rbegin();
            low.erase(low.find(median));
        }

        std::cout << median << " ";
    }

    std::cout << "\n";
}
