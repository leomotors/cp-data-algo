#include <iostream>
#include <map>
#include <set>

class BiMap {
  public:
    // forward is 1-many
    std::map<int, int> forward;
    std::map<int, std::set<int>> backward;

    void insertPair(const int key, const int value) {
        forward[key] = value;
        backward[value].insert(key);
    }

    void increment(const int key, const int inc) {
        auto item = forward.find(key);

        if (item == forward.end()) {
            // not somchai's
            return;
        }

        const auto oldValue = item->second;
        const auto newValue = oldValue + inc;

        item->second = newValue;

        auto oldValSet = backward.find(oldValue);
        oldValSet->second.erase(key);

        if (oldValSet->second.size() == 0) {
            backward.erase(oldValSet);
        }

        backward[newValue].insert(key);
    }

    int findBestSale(int k) const {
        auto lb = backward.lower_bound(k);

        if (lb == backward.begin()) {
            return -1;
        }

        lb--;

        if (lb->first == 0) {
            return -1;
        }

        auto answerSet = lb->second;

        return *answerSet.crbegin();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    BiMap bm;

    for (int i = 0; i < N; i++) {
        int id;
        std::cin >> id;

        bm.insertPair(id, 0);
    }

    for (int i = 0; i < M; i++) {
        int queryType;
        std::cin >> queryType;

        if (queryType == 1) {
            int id, amount;
            std::cin >> id >> amount;

            bm.increment(id, amount);
        } else {
            int k;
            std::cin >> k;
            const auto answer = bm.findBestSale(k);

            if (answer >= 0) {
                std::cout << answer << "\n";
            } else {
                std::cout << "NONE\n";
            }
        }
    }
}
