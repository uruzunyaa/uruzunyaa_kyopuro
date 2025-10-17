#include <algorithm>
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
	map<ll, ll> mp;
    ll n;
    cin >> mp[1] >> mp[5] >> mp[10] >> mp[50] >> mp[100] >> mp[500] >> n;
	vll kind = {1, 5, 10, 50, 100, 500};
	
	rep(i, n) {
        ll x;
        cin >> x;

		for(int j = 5; j >= 0; --j) {
			ll to_use = min(x / kind[j], mp[kind[j]]);
			x -= to_use * kind[j];
			mp[kind[j]] -= to_use;
		}

		if(x != 0) {
			cout << "No" << endl;
			return 0;
		}
    }

	cout << "Yes" << endl;

    return 0;
}
