#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    ll n, k;
    cin >> n >> k;

    rep(i, n) {
        ll a;
        cin >> a;
        if (a % k == 0) cout << a / k << endl;
    }

    return 0;
}
