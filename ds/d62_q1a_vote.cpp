#include <iostream>
#include <map>
#include <set>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, K;
    std::cin >> N >> K;

    std::map<std::string, int> votes;

    for (int i = 0; i < N; i++) {
        std::string candidate;
        std::cin >> candidate;

        votes[candidate]++;
    }

    std::multiset<int> voteFreq;
    for (const auto& [_, freq] : votes) {
        voteFreq.insert(freq);
    }

    auto it = voteFreq.crbegin();

    while (--K) {
        if (it != voteFreq.crend()) {
            it++;
        } else {
            break;
        }
    }

    if (it == voteFreq.crend()) it--;

    std::cout << *it << "\n";
}