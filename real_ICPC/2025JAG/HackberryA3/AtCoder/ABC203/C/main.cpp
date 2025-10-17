#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i < (b); ++i)

int main() {
	int n; cin >> n;
	ll k; cin >> k;
	vector<PLL> ab(n);
	rep(i, n) cin >> ab[i].first >> ab[i].second;
	sort(ab.begin(), ab.end());

	ll ans = 0;
	rep(i, n) {
		ans += k;
		k = 0;
		if(ab[i].first > ans) break;

		while (i < n && ab[i].first <= ans)
		{
			k += ab[i].second;
			i++;
		}
		i--;
	}

	cout << ans + k << endl;

	return 0;
}
