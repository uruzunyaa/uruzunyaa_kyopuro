#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
const ll INF = 1001001001001001001LL;

template <class T>
inline bool chmax(T &a, const T &b) {
	if (a < b) {
		a = b;
		return true;
	}
	return false;
}
template <class T>
inline bool chmin(T &a, const T &b) {
	if (a > b) {
		a = b;
		return true;
	}
	return false;
}

int main() {
	ll m;
	cin >> m;
	string s;
	cin >> s;

	vll t;
	for(char &c : s) {
		t.push_back(c - '0');
	}

	int focus = 1;
	string ans = "";
	for(int i = m - 1; i >= 0; --i) {
		if(t[i] == focus) {
			rep(j, i + 1){
				if(focus == 1) ans += 'A';
				else ans += 'B';
			}
			focus ^= 1;
		}
	}
	
	cout << ans.size() << endl;
	cout << ans << endl;

	return 0;
}
