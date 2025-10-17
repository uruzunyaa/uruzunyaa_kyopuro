#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
const ll INF = 1001001001001001001LL;

template <class T> inline bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> inline bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

int main() {
    ll n, m;
    cin >> n >> m;
    vll c(n + m);
    set<ll> a;
    rep(i, n) {
        cin >> c[i];
        a.insert(c[i]);
    }
    rep(i, m) {
        cin >> c[n + i];
    }

    sort(c.begin(), c.end());

    bool isPrevA = false;
    rep(i, n + m) {
        if (a.count(c[i])) {
            if (isPrevA) {
                cout << "Yes" << endl;
                return 0;
            }
            isPrevA = true;
        }
        else { isPrevA = false; }
    }

    cout << "No" << endl;

    return 0;
}
