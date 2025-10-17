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
    string s;
    cin >> s;

    map<char, ll> mp;
    ll ans = 0;
    bool addedDefault = false;

    rep(i, s.size()) {
        ans += i - mp[s[i]];
        if (i != 0 && mp[s[i]] != 0 && !addedDefault) {
            ans++;
            addedDefault = true;
		}
        mp[s[i]]++;
	}

	cout << ans << endl;

	return 0;
}