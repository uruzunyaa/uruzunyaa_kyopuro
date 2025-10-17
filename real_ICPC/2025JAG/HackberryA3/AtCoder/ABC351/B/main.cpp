#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	ll n; cin >> n;
	vector<string> a(n);
	rep(i, n) cin >> a[i];
	vector<string> b(n);
	rep(i, n) cin >> b[i];

	rep(i, n)rep(j, n){
		if(a[i][j] != b[i][j]){
			cout << i + 1 << ' ' << j + 1 << endl;
			return 0;
		}
	}

	return 0;
}
