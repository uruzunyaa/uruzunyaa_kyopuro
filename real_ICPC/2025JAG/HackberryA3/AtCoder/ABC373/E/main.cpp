#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
constexpr ll INF = 1001001001001001001LL;
constexpr int INF32 = 1001001001;
constexpr ll MOD = 998244353;
constexpr ll MOD107 = 1000000007;

// Linear Algebra ////////////////////////////////////////////////
const double Rad2Deg = 180.0 / M_PI;
const double Deg2Rad = M_PI / 180.0;
//////////////////////////////////////////////////////////////////

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

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

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) os << " ";
    }
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& vv) {
	for (size_t i = 0; i < vv.size(); ++i) {
		os << vv[i];
		if (i != vv.size() - 1) os << "\n";
    }
    return os;
}
template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
	assert(v.size() > 0);
	for (int i = 0; i < v.size(); ++i) is >> v[i];
	return is;
}
template <typename T>
istream& operator>>(istream& is, vector<vector<T>>& vv) {
	assert(vv.size() > 0);
	for (int i = 0; i < vv.size(); ++i) is >> vv[i];
	return is;
}

struct phash {
	template<class T1, class T2>
    inline size_t operator()(const pair<T1, T2> & p) const {
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);

		size_t seed = h1 + h2; 
		h1 = ((h1 >> 16) ^ h1) * 0x45d9f3b;
        h1 = ((h1 >> 16) ^ h1) * 0x45d9f3b;
        h1 = (h1 >> 16) ^ h1;
        seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		h2 = ((h2 >> 16) ^ h2) * 0x45d9f3b;
        h2 = ((h2 >> 16) ^ h2) * 0x45d9f3b;
        h2 = (h2 >> 16) ^ h2;
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};





int solve() {
	ll n, m, k; cin >> n >> m >> k;
	vll a(n); cin >> a;
	ll opened = 0;

	map<ll, ll> cnt;
	rep(i, n) {
		cnt[a[i]]++;
		opened += a[i];
	}
	k -= opened;

	map<ll, ll> cntsum;
	{
		ll sumVal = 0;
		for (auto it = cnt.rbegin(); it != cnt.rend(); ++it) {
			sumVal += it->second;
			cntsum[it->first] = sumVal;
		}
	}

	// 差分（最小、最大）を求める
	vector<PLL> diff(n);
	{
		ll prevKey = cnt.begin()->first;
		ll prevVal = cnt.begin()->second;
		ll i = 0;
		for (auto it = cnt.begin(); it != cnt.end(); ++it, ++i) {
			diff[i] = {it->first - prevKey, (it->first - prevKey) * prevVal};
			prevKey = it->first;
			prevVal = it->second;
		}
	}

	// 差分の累積和
	vector<PLL> sum(n + 1);
	rep(i, n) {
		sum[i + 1].first = sum[i].first + diff[i].first;
		sum[i + 1].second = sum[i].second + diff[i].second;
	}



	auto check = [&](ll x, ll add) {
		ll newVal = x + add;
		auto lower = cntsum.lower_bound(newVal);
		if (lower != cntsum.end() && lower->second + 1 >= m) return false;

		ll left = m - 1 - lower->second;
		ll leftK = k - add;

		// 一つ前の差分を見て、leftK以下かつ全員を入れた時にm未満ならOK
		auto prev = lower;
		--prev;
		ll prevDiff = prev->first;
		ll prevSum = prev->second;

		ll Min = newVal - prevDiff;
		ll Max = (newVal - prevDiff) * cnt[prevDiff];

		if (Min <= leftK && leftK % Min > left) {
			return false;
		}


	};

	rep(i, n) {
		ll l = 0, r = k;
		while (r - l > 1) {
			ll mid = (l + r) / 2;
			if (check(a[i], mid)) l = mid;
			else r = mid;
		}

		cout << l << endl;
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
