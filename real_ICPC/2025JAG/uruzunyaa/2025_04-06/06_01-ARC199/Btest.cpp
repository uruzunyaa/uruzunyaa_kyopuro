#include <bits/stdc++.h>
using namespace std;

vector<long long> xor_basis(const vector<long long>& A) {
    vector<long long> basis;
    for (long long x : A) {
        for (long long b : basis) {
            x = min(x, x ^ b);  // bを使ってxを簡単にできるか
        }
        if (x != 0) basis.push_back(x);
    }
    return basis;
}

int main() {
    vector<long long> A = {3, 5, 7, 9};
    vector<long long> basis = xor_basis(A);

    cout << "XOR基底:" << endl;
    for (long long b : basis) {
        cout << b << " ";
    }
    cout << endl;
    return 0;
}
