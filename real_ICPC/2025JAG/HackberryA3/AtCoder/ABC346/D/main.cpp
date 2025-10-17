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

template <typename Container,
          typename = std::enable_if_t<
              !std::is_same_v<Container, std::string> &&
              std::is_convertible_v<decltype(std::declval<Container>().begin()),
                                    typename Container::iterator>>>
ostream &operator<<(ostream &os, const Container &container) {
    auto it = container.begin();
    auto end = container.end();

    if (it != end) {
        os << *it;
        ++it;
    }
	for (; it != end; ++it) {
		os << " " << *it;
	}
    return os;
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
	ll n; cin >> n;
	string s; cin >> s;
	vll c(n); cin >> c;

	vll dp_0_left(n, 0), dp_0_right(n, 0);
	vll dp_1_left(n, 0), dp_1_right(n, 0);
	ll sum0 = 0, sum1 = 0;
	/*
	* 0 0 0 1 1
	* 3 9 2 6 4
	*
	* 0 1 0 1 0 ：目標
	* 1 0 1 0 1 ：目標
	*
	* 0 9 9 9 13 : 左から0スタート
	* 3 3 5 11 11 : 左から1スタート
	* 13 13 4 4 4 : 右から0スタート
	* 11 8 8 6 0 : 右から1スタート
	*
	*
	* 1 0 0 1
	* 1 2 3 4
	*
	* 1 3 3 3 : 左から0スタート
	* 0 0 3 7 : 左から1スタート
	* 7 7 7 4 : 右から0スタート
	* 3 2 0 0 : 右から1スタート
	*/
	rep(i, n) {
		if (i % 2 == 0) {
			if (s[i] == '0') sum1 += c[i];
			else sum0 += c[i];
		} else {
			if (s[i] == '0') sum0 += c[i];
			else sum1 += c[i];
		}
		dp_0_left[i] = sum0;
		dp_1_left[i] = sum1;
	}
	sum0 = 0, sum1 = 0;
	for (int i = n - 1; i >= 0; --i) {
		if ((n - 1 - i) % 2 == 0) {
			if (s[i] == '0') sum1 += c[i];
			else sum0 += c[i];
		} else {
			if (s[i] == '0') sum0 += c[i];
			else sum1 += c[i];
		}
		dp_0_right[i] = sum0;
		dp_1_right[i] = sum1;
	}

	ll ans = INF;
	rep(i, n - 1) {
		// 左の要素が奇数個のとき
		if (i % 2 == 0) {
			// 中央を0にする
			ll cost = dp_0_left[i] + ((n - (i + 1)) % 2 == 0 ? dp_1_right[i + 1] : dp_0_right[i + 1]);
			chmin(ans, cost);

			// 中央を1にする
			cost = dp_1_left[i] + ((n - (i + 1)) % 2 == 0 ? dp_0_right[i + 1] : dp_1_right[i + 1]);
			chmin(ans, cost);
		}
		// 左の要素が偶数個のとき
		else {
			// 中央を0にする
			ll cost = dp_1_left[i] + ((n - (i + 1)) % 2 == 0 ? dp_1_right[i + 1] : dp_0_right[i + 1]);
			chmin(ans, cost);

			// 中央を1にする
			cost = dp_0_left[i] + ((n - (i + 1)) % 2 == 0 ? dp_0_right[i + 1] : dp_1_right[i + 1]);
			chmin(ans, cost);
		}
	}

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
