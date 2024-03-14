#include <iostream>
#include <vector>

int arr[200005];
int pos[200005];
int n;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m;
    std::cin >> n >> m;

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
        pos[arr[i]] = i;
    }

    for (int i = 0; i < m; i++) {
        int q;
        std::cin >> q;

        int dist = pos[q] - q + 1;

        int nless = 0;

        for (int j = pos[q] + 1; j < n; j++) {
            if (arr[j] < q) {
                nless++;
            }
        }

        std::cout << dist + nless << "\n";
    }
}
