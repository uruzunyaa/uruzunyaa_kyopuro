#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	string s, t;
	cin >> s >> t;

	ll n = 0;
	rep(i, t.size()) {
		if(s[n] == t[i]) {
			cout << i + 1 << endl;
			n++;
		}
	}

	return 0;
}
