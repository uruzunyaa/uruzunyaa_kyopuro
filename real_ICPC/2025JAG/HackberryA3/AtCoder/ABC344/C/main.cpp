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
	int n, m, l;
	cin >> n;
	vl a(n);
	rep(i, n) cin >> a[i];
	cin >> m;
	vl b(m);
	rep(i, m) cin >> b[i];
	cin >> l;
	vl c(l);
	rep(i, l) cin >> c[i];

	unordered_set<ll> sum;
	rep(i, n)
	{
		rep(j, m)
		{
			rep(k, l)
			{
				sum.insert(a[i] + b[j] + c[k]);
			}
		}
	}

	int q;
	cin >> q;
	rep(i, q)
	{
		ll x;
		cin >> x;
		if (sum.count(x))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	return 0;
}