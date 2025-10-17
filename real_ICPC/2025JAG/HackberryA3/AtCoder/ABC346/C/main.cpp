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
    ll n, k;
    cin	>> n >> k;

    ll sum = k * (k + 1) / 2;
    unordered_set<ll> done;
    rep(i, n) {
        ll a;
        cin >> a;
        if (done.count(a) == 0 && a <= k) {
            sum -= a;
            done.insert(a);
		}
    }

    cout << sum << endl;

	return 0;
}