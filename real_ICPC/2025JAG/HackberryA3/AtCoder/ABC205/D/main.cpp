// #二分探索
// 数列aを含まない数列のk番目の要素を求める
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i <= (b); ++i)

int main() {
	int n, q;
	cin >> n >> q;
	vl a(n);
	rep(i, n) cin >> a[i];

	auto f = [&](ll x, ll k) {
		auto it = upper_bound(a.begin(), a.end(), x);
		return k <= x - (it - a.begin());
	};

	rep(i, q){
		ll k; cin >> k;

		ll l = -1, r = LLONG_MAX - 1;
		while (r - l > 1) {
			ll mid = (l + r) / 2;
			if (f(mid, k)) r = mid;
			else l = mid;
		}

		cout << r << endl;
	}

	return 0;
}
