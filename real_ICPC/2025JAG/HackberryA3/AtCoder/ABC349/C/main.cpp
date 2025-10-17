// #部分文字列
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main() {
    string s, t;
    cin >> s >> t;

	transform(s.begin(), s.end(), s.begin(), ::toupper);

    ll n = 0;
    rep(i, s.size()) {
        if (n == 2 && (t[n] == 'X' || s[i] == t[n])) {
            cout << "Yes" << endl;
            return 0;
        }

        if (s[i] == t[n]) { n++; }
    }
	if(n == 2 && t[n] == 'X') {
		cout << "Yes" << endl;
		return 0;
	}

    cout << "No" << endl;

    return 0;
}
