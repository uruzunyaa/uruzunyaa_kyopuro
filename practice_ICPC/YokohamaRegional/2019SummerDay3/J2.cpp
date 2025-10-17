#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for (ll i = a; i <= (ll)b; ++i)

int main() {
    ll n;
	cin>>n;
	if(__popcount(n)!=1){
		cout<<"No"<<endl;
		return 0;
	}

	vector<vector<ll>> ans(n, vector<ll>(n, -1));
	auto dfs = [&](auto dfs, PLL s, PLL g, ll used) -> ll {
		ll size = g.first - s.first + 1;

		PLL lls = {s.first + size / 2, s.second};
		PLL llg = {g.first, g.second - size / 2};
		loop(y, lls.first, llg.first) {
			loop(x, lls.second, llg.second) {
				ll val = (used + (x - lls.second) + (y - lls.first)) % (size / 2) + (used + 1);
				ans[y][x] = val;
			}
		}
		used += size / 2;

		PLL urs = {s.first, s.second + size / 2};
		PLL urg = {g.first - size / 2, g.second};
		loop(y, urs.first, urg.first) {
			loop(x, urs.second, urg.second) {
				ll val = (used + (x - urs.second) + (y - urs.first)) % (size / 2) + (used + 1);
				ans[y][x] = val;
			}
		}
		used += size / 2;

		PLL uls = {s.first, s.second};
		PLL ulg = {g.first - size / 2, g.second - size / 2};
		ll nextsize = ulg.first - uls.first + 1;
		if (nextsize > 1) {
			used = dfs(dfs, uls, ulg, used);

			PLL lrs = {s.first + size / 2, s.second + size / 2};
			PLL lrg = {g.first, g.second};
			loop(y, lrs.first, lrg.first) {
				loop(x, lrs.second, lrg.second) {
					ll uly = y - lrs.first + uls.first;
					ll ulx = x - lrs.second + uls.second;
					ans[y][x] = ans[uly][ulx];
				}
			}
		}

		return used;
	};
	if (n != 1) dfs(dfs, {0, 0}, {n - 1, n - 1}, 0);

	cout << "Yes" << endl;
	rep(y, n) {
		rep(x, n) {
			if (y == x) ans[y][x] = 2 * n - 1;
			cout << ans[y][x] << " ";
		}
		cout << endl;
	}
}