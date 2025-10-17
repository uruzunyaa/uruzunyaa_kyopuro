#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

void f(ll x, map<ll, ll> &mp, ll &score) {
    if (11 < x) return;
    mp[x]++;
    if (mp[x] == 2) {
        score += x;
		mp[x] = 0;
        f(x + 1, mp, score);
    }
}

int main() {
    ll t;
    cin >> t;
    rep(i, t) {
        ll n;
        cin >> n;
        map<ll, ll> mp;
        ll score = 0;

		rep(j, n){
			ll a; cin >> a;
			f(a, mp, score);
		}

		cout << score << endl;
    }

    return 0;
}
