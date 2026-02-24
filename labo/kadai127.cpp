#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int main() {
    dsu uf(5);
    uf.merge(0, 1);
    cout << uf.same(0, 1) << "\n"; // 1 が出ればOK
}