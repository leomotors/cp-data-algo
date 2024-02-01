#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

inline int qsrange(int* arr, int start, int end) {
    return arr[end] - arr[start];
}

bool isvirus(int* qs, int start, int end) {
    if (end - start <= 2) {
        return true;
    }

    int mid = (start + end) / 2;
    if (abs(qsrange(qs, start, mid) - qsrange(qs, mid, end)) > 1) {
        return false;
    }

    return isvirus(qs, start, mid) && isvirus(qs, mid, end);
}

int main(void) {
    int n, k;
    scanf("%d %d", &n, &k);

    int virus_size = 1 << k;
    int arr[1 << 16];
    int qs[1 << 16];
    qs[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < virus_size; j++) {
            scanf("%d", &arr[j]);
            qs[j + 1] = qs[j] + arr[j];
        }

        printf("%s\n", isvirus(qs, 0, virus_size) ? "yes" : "no");
    }
}
