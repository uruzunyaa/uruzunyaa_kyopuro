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
    ll n, k;
    cin >> n >> k;

    vll x(n);
    rep(i, n) cin >> x[i];

    if (0 < k) {
        sort(x.begin(), x.end());
        cout << "Yes" << endl;
        for (auto xi : x) {
            cout << xi << " ";
        }
        return 0;
    }

    vll posi;
    vll nega;
    rep(i, n) {
        if (x[i] < 0) { nega.push_back(x[i]); }
        else { posi.push_back(x[i]); }
    }
    sort(posi.begin(), posi.end());
    sort(nega.begin(), nega.end(), greater<ll>());

    vll ans;
    ll now = 0;
    int pi = 0;
    int ni = 0;
    while (pi != posi.size() || ni != nega.size()) {
        if (ni != nega.size() && now + nega[ni] >= k) {
            ans.push_back(nega[ni]);
            now += nega[ni];
            ni++;
        }
        else if (pi != posi.size()) {
            ans.push_back(posi[pi]);
            now += posi[pi];
            pi++;
        }
        else {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;
    for (auto a : ans) {
        cout << a << " ";
    }

    return 0;
}
