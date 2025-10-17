#include <bits/stdc++.h>
#include <climits>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define rrep(i, n) for(ll i = n - 1; i >= 0; --i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
#define nC2(n) n * (n - 1) / 2
constexpr ll INF = 9009009009009009009LL;
constexpr int INF32 = 2002002002;
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
	for (size_t i = 0; i < v.size(); ++i) is >> v[i];
	return is;
}
template <typename T>
istream& operator>>(istream& is, vector<vector<T>>& vv) {
	assert(vv.size() > 0);
	for (size_t i = 0; i < vv.size(); ++i) is >> vv[i];
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




template <typename T>
struct RollingHash {
private:
	vector<unsigned long long> pow_base;
	vector<unsigned long long> hash;
public:
	unsigned long long base;
	static const unsigned long long mod = 2147483647;

	static unsigned long long generate_base() {
		mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
		return uniform_int_distribution<unsigned long long>(1, mod - 1)(rnd);
	}

	/**
	* @brief Iterable<T>のローリングハッシュを計算する O(n)
	* @param s 文字列やvectorなどの添字アクセス可能なオブジェクト
	* @param base ハッシュの基数。デフォルトはランダムに生成される
	*/
	template <typename Iterable>
	RollingHash(Iterable s, unsigned long long base = generate_base()): pow_base(s.size() + 1, 1), hash(s.size() + 1, 0) {
		for (int i = 0; i < s.size(); ++i){
			hash[i + 1] = ((hash[i] * base) % mod + (unsigned long long)s[i]) % mod;
			pow_base[i + 1] = (pow_base[i] * base) % mod;
		}
	}

	/**
	* @brief [l, r) の連続部分列のハッシュ値を返す O(1)
	*/
	unsigned long long get(int l, int r) {
		return (hash[r] - (hash[l] * pow_base[r - l]) % mod + mod) % mod;
	}
};

int solve() {
	string s; cin >> s;
	
	ull base = RollingHash<char>::generate_base();
	RollingHash<char> rh(s, base);
	string s_rev = s;
	reverse(all(s_rev));
	RollingHash<char> rh_rev(s_rev, base);

	ll mx = 0;
	rep(i, s.size()) {
		ll lhash = rh.get(s.size() - i - 1, s.size());
		ll rhash = rh_rev.get(0, i + 1);
		if (lhash == rhash) {
			chmax(mx, i + 1);
		}
	}

	string ans = s;
	loop(i, mx, s.size() - 1) {
		ans += s_rev[i];
	}

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
