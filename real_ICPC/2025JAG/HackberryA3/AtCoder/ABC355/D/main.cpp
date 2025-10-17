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
	ll n; cin >> n;

	set<int> s;
	map<int, int> idx;
	vector<P> lr(n);
	rep(i, n){
		cin >> lr[i].first >> lr[i].second;
		s.insert(lr[i].first);
		s.insert(lr[i].second);
	}

	for(auto itr = s.begin(); itr != s.end(); ++itr){
		idx[*itr] = idx.size();
	}



	vector<ll> add(s.size(), 0);
	vector<ll> minus(s.size(), 0);
	rep(i, n){
		add[idx[lr[i].first]]++;
		minus[idx[lr[i].second]]++;
	}

	ll ans = add[0] * (add[0] - 1) / 2;
	ll cnt = add[0] - minus[0];
	for(int i = 1; i < s.size(); ++i) {
		if(add[i] > 0 && cnt > 0){
			// cnt + add[i] から 2つを選ぶ組み合わせ
			ans += (cnt + add[i]) * (cnt + add[i] - 1) / 2;
			ans -= cnt * (cnt - 1) / 2;
		}
		cnt += add[i] - minus[i];
	}

	cout << ans << endl;

	return 0;
}
