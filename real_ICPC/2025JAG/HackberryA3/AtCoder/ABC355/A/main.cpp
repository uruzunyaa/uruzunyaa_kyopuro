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
	ll a, b; cin >> a >> b;

	if (a == b){
		cout << -1 << endl;
		return 0;
	}

	if(a == 1){
		if (b == 2) cout << 3 << endl;
		else cout << 2 << endl;
	}
	else if(a == 2){
		if (b == 1) cout << 3 << endl;
		else cout << 1 << endl;
	}
	else if(a == 3){
		if (b == 1) cout << 2 << endl;
		else cout << 1 << endl;
	}

	return 0;
}
