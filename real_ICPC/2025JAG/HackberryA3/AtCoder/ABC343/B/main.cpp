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
	int n; cin >> n;

	rep(i, n) {
		rep(j, n) {
			int a; cin >> a;
			if (a == 1) cout << j + 1 << " ";
		}

		cout << endl;
	}

	return 0;
}
