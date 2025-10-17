#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define ALL(v) v.begin(),v.end()
int N;
using pii = pair<int,int>;

struct BIT {
	int n;
	vector<ll> d;
	BIT(int n) : n(n), d(n+1) {}

	void add(int idx, ll val) {
		idx++;
		for (int i = idx; i <= n; i+=i&-i) {
			d[i] += val;
		}
	}
	ll sum(int idx) {
		ll res = 0;
		for (int i = idx; i > 0; i -= i&-i) {
			res += d[i];
		}
		return res;
	}
	ll sum(int l, int r) {
		return sum(r) - sum(l);
	}
};

int main() {
	cin >> N;
	int max = 1e6 + 2;
	vector<vector<int>> qs(max);
	vector<int> p(N),q(N);
	for (int i = 0; i < N; ++i) {
		cin >> p[i];
	}
	for (int i = 0; i < N; ++i) {
		cin >> q[i];
		qs[p[i]].push_back(q[i]);
	}
	BIT L(max),R(max);
	for (int i = 0; i < max; ++i) {
		for (int q : qs[i]) {
			R.add(q, 1);
		}
	}
	ll ans = 0;
	for (int p = 0; p < max; ++p) {
		for (int q : qs[p]) R.add(q,-1);
		if (p-1 >= 0) for (int q : qs[p-1]) L.add(q,1);
		for (int q : qs[p]) {
			ll l = L.sum(q);
			ll r = R.sum(q+1,max);
			// cerr << p << " " << q << " " << l << " " << r << endl;
			ans += l * r;
		}
	}
	cout << ans << endl;
}