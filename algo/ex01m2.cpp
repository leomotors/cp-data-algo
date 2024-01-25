#include <iostream>
#include <vector>

void merge(std::vector<int>& src, std::vector<int>& dst, int aBegin, int aEnd,
           int bBegin, int bEnd, int& cum) {
    int i = aBegin;
    int j = bBegin;

    int q = aBegin;

    while (true) {
        if (i >= aEnd && j >= bEnd) {
            break;
        }

        if (j >= bEnd) {
            dst[q++] = src[i++];
            continue;
        }

        if (i >= aEnd) {
            dst[q++] = src[j++];
            continue;
        }

        if (src[i] <= src[j]) {
            dst[q++] = src[i++];
            continue;
        } else {
            dst[q++] = src[j++];
            cum += aEnd - i;
            continue;
        }
    }

    for (int i = aBegin; i < bEnd; i++) {
        src[i] = dst[i];
    }
}

void divide(std::vector<int>& src, std::vector<int>& dst, int begin, int end,
            int& cum) {
    int mid = (begin + end) / 2;

    if (begin + 1 < end) {
        divide(src, dst, begin, mid, cum);
        divide(src, dst, mid, end, cum);
        merge(src, dst, begin, mid, mid, end, cum);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> ori(N);
    std::vector<int> res(N);

    for (int i = 0; i < N; i++) {
        std::cin >> ori[i];
    }

    int cum = 0;
    divide(ori, res, 0, N, cum);

    std::cout << cum << "\n";
}