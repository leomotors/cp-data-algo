#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void member_multiply(vector<int> &v,
                     vector<pair<vector<int>::iterator, int>> &multiply) {
    auto multiplyCopy = multiply;

    std::sort(multiplyCopy.begin(), multiplyCopy.end());
    auto multiplyIt = multiplyCopy.cbegin();

    std::vector<int> result;
    for (auto it = v.cbegin(); it != v.cend(); it++) {
        if (multiplyIt == multiplyCopy.cend() || it != multiplyIt->first) {
            result.push_back(*it);
        } else {
            for (int i = 0; i <= multiplyIt->second; i++) {
                result.push_back(*it);
            }
            multiplyIt++;
        }
    }

    v.clear();
    std::copy(result.cbegin(), result.cend(), std::back_inserter(v));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    vector<pair<vector<int>::iterator, int>> multiply(m);
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        multiply[i].first = v.begin() + a;
        multiply[i].second = b;
    }
    member_multiply(v, multiply);
    cout << "======= result ========" << endl;
    cout << v.size() << endl;
    for (auto &x : v) {
        cout << x << " ";
    }
    cout << endl;
}
