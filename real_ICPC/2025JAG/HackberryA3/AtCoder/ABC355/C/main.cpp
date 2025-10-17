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
	ll n, t; cin >> n >> t;

	set<ll> UtoD;
	set<ll> DtoU;
	for(ll x = 1, y = 1; x <= n; ++x, ++y){
		UtoD.insert(n * (y - 1) + x);
	}
	for(ll x = 1, y = n; x <= n; ++x, --y){
		DtoU.insert(n * (y - 1) + x);
	}

	vll colCnt(n, 0);
	vll rowCnt(n, 0);
	ll UtoDCnt = 0;
	ll DtoUCnt = 0;

	rep(i, t){
		ll a; cin >> a;
		if(UtoD.count(a)){
			UtoDCnt++;
		}
		if(DtoU.count(a)){
			DtoUCnt++;
		}

		ll y = (a - 1) / n;
		ll x = (a - 1) % n;
		colCnt[x]++;
		rowCnt[y]++;

		if(colCnt[x] == n || rowCnt[y] == n || UtoDCnt == n || DtoUCnt == n){
			cout << i + 1 << endl;
			return 0;
		}
	}

	cout << -1 << endl;

	return 0;
}
