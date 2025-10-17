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

int main()
{
	int t;
	cin >> t;

	auto f = [&](ll x, ll k)
	{
		ll debug = x;
		ll res = 0;

		ll digit = 0;
		ll exp = 0;

		while (x > 0)
		{
			digit = x % 10;
			x /= 10;

			res += digit * pow(9, exp);
			exp++;
		}

		cout << debug << " = " << res << " = " << (k <= res ? "true" : "false") << endl;
		return k <= res;
	};

	f(20, 25);

	rep(i, t)
	{
		ll k;
		cin >> k;

		ll l = 0;
		ll r = 1e12 + 10000;
		while (r - l > 1)
		{
			ll mid = (l + r) / 2;
			if (f(mid, k))
				r = mid;
			else
				l = mid;
		}

		cout << r << endl;
	}

	return 0;
}
