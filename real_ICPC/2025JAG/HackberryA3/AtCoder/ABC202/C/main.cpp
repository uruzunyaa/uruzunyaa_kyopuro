#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i < (b); ++i)

int main() {
	int n; cin >> n;
	vector<int> a(n), b(n), c(n);
	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];
	rep(i, n) {
		int x; cin >> x;
		c[i] = b[x - 1];
	}

	vector<int> mapA(n + 1);
	rep(i, n) mapA[a[i]]++;
	vector<int> mapB(n + 1);
	rep(i, n) mapB[c[i]]++;

	ll ans = 0;
	rep(i, n + 1) {
		ans += (ll)mapA[i] * mapB[i];
	}

	cout << ans << endl;
	return 0;
}
