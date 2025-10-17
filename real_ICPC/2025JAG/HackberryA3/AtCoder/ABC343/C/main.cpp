#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using P = pair<int, int>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i < (b); ++i)

int main() {
	ll n; cin >> n;

	ll max = 0;
	for (ll i = 1; i <= n; ++i)
	{
		ll cb = i * i * i;
		if(cb > n) break;

		string s = to_string(cb);
		bool ok = true;
		rep(j, s.size() / 2 + 1)
		{
			if (s[j] != s[s.size() - j - 1])
			{
				ok = false;
				break;
			}
		}

		if (ok)
		{
			max = cb;
		}
	}

	std::cout << max << endl;

	return 0;
}