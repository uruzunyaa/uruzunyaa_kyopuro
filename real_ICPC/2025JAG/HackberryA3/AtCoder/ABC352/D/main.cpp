#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main() {
    ll n, k;
    cin >> n >> k;

    vll indexA(n);
    rep(i, n) {
        ll a;
        cin >> a;
        indexA[a - 1] = i;
    }

    map<ll, ll> mp;
    rep(i, k) { // 最初にk個の要素を追加
        mp[indexA[i]] = 1;
    }

    ll ans = 1001001001001001001;
    loop(i, k, n - 1) {
        ll minIndex = mp.begin()->first;
        ll maxIndex = mp.rbegin()->first;
        ans = min(ans, maxIndex - minIndex);

        mp.erase(indexA[i - k]);
        mp[indexA[i]] = 1;
    }
    ll minIndex = mp.begin()->first;
    ll maxIndex = mp.rbegin()->first;
    ans = min(ans, maxIndex - minIndex);

    cout << ans << endl;

    return 0;
}
