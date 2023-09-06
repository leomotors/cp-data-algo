#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class MaxMap {
  private:
    std::map<int, int> forward;
    std::map<int, std::set<int>> reverse;

    void mutate(int key, int oldValue, int newValue) {
        reverse[oldValue].erase(key);
        if (reverse[oldValue].size() == 0) {
            reverse.erase(oldValue);
        }

        reverse[newValue].insert(key);
    }

  public:
    void update(int key, int value) {
        int oldValue = forward[key];
        int newValue = std::max(oldValue, value);

        if (oldValue != newValue) {
            forward[key] = newValue;
            mutate(key, oldValue, newValue);
        }
    }

    int getMinMax() {
        return reverse.begin()->first;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> power, type;

    MaxMap team;

    for (int i = 0; i < n; i++) {
        int t;
        std::cin >> t;
        power.push_back(t);
    }

    for (int i = 0; i < n; i++) {
        int t;
        std::cin >> t;
        type.push_back(t);
    }

    for (int i = 0; i < m; i++) {
        team.update(i, 1);
    }

    for (int i = 0; i < n; i++) {
        team.update(type[i], power[i]);
        std::cout << team.getMinMax() << " ";
    }

    std::cout << "\n";
}
