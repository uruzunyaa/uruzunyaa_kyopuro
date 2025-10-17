#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	string s; cin >> s;
	map<char, ll> mp;

	for (char c : s) {
		mp[c]++;
	}

	bool ok = true;
	rep(i, 150) {
		ll count = 0;
		for (auto kv : mp) {
			if (kv.second == i) {
				count++;
			}
		}

		if(count != 0 && count != 2) {
			ok = false;
			break;
		}
	}

	cout << (ok ? "Yes" : "No") << endl;

	return 0;
}
