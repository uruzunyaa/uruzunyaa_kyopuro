// #bit全探索
#include <bits/stdc++.h>
#include <bitset>
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
    ll n, m, k;
    cin >> n >> m >> k;

    vvll a(m, vll());
    vll success(m, 0);
    rep(i, m) {
        ll c;
        cin >> c;
        rep(j, c) {
            ll x;
            cin >> x;
            a[i].push_back(x);
        }

        char r;
        cin >> r;
        success[i] = r == 'o' ? 1 : 0;
    }

    ll ans = 0;
	uint bit = 0;
	while(bit <= (1 << n) - 1) {
		bool ok = true;
		rep(i, m) {
			int cnt = 0;
			for(auto x : a[i]) {
				if(bit & (1 << (x - 1))) ++cnt;
			}

			if(success[i] && cnt < k) {
				ok = false;
				break;
			}
			else if(!success[i] && cnt >= k) {
				ok = false;
				break;
			}
		}	

		if(ok) ++ans;
		++bit;
	}


	cout << ans << endl;
    return 0;
}
