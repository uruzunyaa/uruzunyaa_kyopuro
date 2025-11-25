#include <bits/stdc++.h>
#include <atcoder/convolution>
using namespace std;

int main() {
    vector<long long> a = {1, 2, 3};
    vector<long long> b = {4, 5, 6};
    auto c = atcoder::convolution(a, b);
    for (auto x : c) cout << x << " ";
}
