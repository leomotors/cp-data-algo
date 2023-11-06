#include <iostream>
#include <queue>

int n, k;
int heap[50005];
uint32_t queue[50005];

class StaticQueue {
  public:
    uint32_t mSize = 0;
    uint32_t mFront = 0;

  public:
    const uint32_t mCap = 50000;

    // inline bool empty() const { return mSize == 0; }

    void push(uint32_t n) {
        queue[(mFront + mSize++) % mCap] = n;
    }

    uint32_t pop() {
        uint32_t tmp = queue[mFront];
        mFront = (mFront + 1) % mCap;
        mSize--;

        return tmp;
    }

    void clear() {
        mSize = 0;
        mFront = 0;
    }
};

StaticQueue frontier;

bool checkHeap() {
    // std::queue<int> frontier;
    frontier.clear();
    frontier.push(0);

    while (frontier.mSize) {
        // int fr = frontier.front();
        // frontier.pop();
        const auto fr = frontier.pop();

        if (fr > 0 && heap[fr] >= heap[(fr - 1) / k]) {
            return false;
        }

        for (uint32_t i = 1; i <= k; i++) {
            const auto toAdd = k * fr + i;
            if (toAdd >= n) break;
            frontier.push(toAdd);
        }
    }

    return true;
}

inline void run() {
    std::cin >> n >> k;

    for (int i = 0; i < n; i++) {
        std::cin >> heap[i];
    }

    std::cout << (checkHeap() ? "true\n" : "false\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m;
    std::cin >> m;

    while (m--) {
        run();
    }
}
