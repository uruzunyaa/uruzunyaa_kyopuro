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
	string num = s.substr(3, 3);
	ll n = stoi(num);

	if (1 <= n && n <= 349 && n != 316) cout << "Yes" << endl;
	else cout << "No" << endl;

	return 0;
}
