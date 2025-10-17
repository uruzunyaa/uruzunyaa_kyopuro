#include <bits/stdc++.h>
#include <sys/types.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for(ll i = 0; i < static_cast<ll>(n); ++i)
#define rrep(i, n) for(ll i = static_cast<ll>(n) - 1; i >= 0; --i)
#define loop(i, a, b) for(ll i = static_cast<ll>(a); i <= static_cast<ll>(b); ++i)
#define all(v) v.begin(), v.end()
#define nC2(n) n * (n - 1) / 2
constexpr ll INF = 9009009009009009009LL;
constexpr int INF32 = 2002002002;
constexpr ll MOD = 998244353;
constexpr ll MOD107 = 1000000007;

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
	vector<int64_t> pow_bases;
	vector<int64_t> hashes;
	vector<int64_t> inv_bases;
	vector<int64_t> rev_hashes;

	int64_t ext_gcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
		if (b == 0) {
			x = 1;
			y = 0;
			return a;
		}
		int64_t d = ext_gcd(b, a % b, y, x);
		y -= a / b * x;
		return d;
	}
	int64_t inv(int64_t a, int64_t mod) {
		int64_t x, y;
		ext_gcd(a, mod, x, y);
		return (x % mod + mod) % mod;
	}

	int64_t mul(int64_t a, int64_t b) {
		__int128 res = a;
		res *= b;
		res %= mod;
		return (int64_t)res;
	}

public:
	const int64_t base;
	const int64_t inv_base = 0;
	static const int64_t mod = (1LL << 61) - 1;

	static int64_t generate_base() {
		mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
		return uniform_int_distribution<int64_t>(1, mod - 1)(rnd);
	}

	/**
	 * @brief ローリングハッシュのコンストラクタ O(1)
	 * @param base ハッシュの基数。デフォルトはランダムに生成される
	 * @param use_rev 逆方向のハッシュを計算するかどうか。デフォルトはtrue
	 * @param inv_base 逆方向のハッシュを計算する際の基数の逆元。use_revがtrueでinv_baseが0の場合、自動的に計算される O(log)
	 */
	RollingHash(int64_t base = generate_base(), bool use_rev = true, int64_t inv_base = 0): base(base), inv_base(use_rev && inv_base == 0 ? inv(base, mod) : inv_base) {
		assert(1 <= base && base < mod && "ローリングハッシュの基数は1以上mod未満でなければなりません");

		pow_bases.push_back(1);
		hashes.push_back(0);
		if (use_rev) {
			inv_bases.push_back(1);
			rev_hashes.push_back(0);
		}
	}
	/**
	* @brief Iterable<T>のローリングハッシュを計算する O(n)
	* @param s 文字列やvectorなどの添字アクセス可能なオブジェクト
	* @param base ハッシュの基数。デフォルトはランダムに生成される
	* @param use_rev 逆方向のハッシュを計算するかどうか。デフォルトはtrue
	* @param inv_base 逆方向のハッシュを計算する際の基数の逆元。use_revがtrueでinv_baseが0の場合、自動的に計算される O(log)
	*/
	template <typename Iterable>
	RollingHash(Iterable s, int64_t base = generate_base(), bool use_rev = true, int64_t inv_base = 0): RollingHash(base, use_rev, inv_base) {
		pow_bases.reserve(s.size() + 1);
		hashes.reserve(s.size() + 1);
		if (use_rev) {
			inv_bases.reserve(s.size() + 1);
			rev_hashes.reserve(s.size() + 1);
		}
		for (int i = 0; i < static_cast<int>(s.size()); ++i){
			push_back(s[i]);
		}
	}

	void push_back(T c) {
		// hashes[i] = (hashes[i - 1] * base + (unsigned int64_t)c) % mod;
		// 順方向は重みが軽い方に追加。123 -> 123
		hashes.push_back((mul(hashes.back(), base) + (int64_t)c) % mod);
		if (pow_bases.size() < hashes.size()) pow_bases.push_back(mul(pow_bases.back(), base));

		// rev_hashes[i] = (base^i * c + rev_hashes[i - 1]) % mod;
		// 逆方向は重みが重い方に追加。123 -> 321
		if (inv_base != 0) {
			rev_hashes.push_back((mul(pow_bases[rev_hashes.size() - 1], (int64_t)c) + rev_hashes.back()) % mod);
			if (inv_bases.size() < rev_hashes.size()) inv_bases.push_back(mul(inv_bases.back(), inv_base));
		}
	}
	void pop_back() {
		assert(1 < (int)hashes.size() && "空のローリングハッシュから要素を削除することはできません");
		hashes.pop_back();
		if (rev_hashes.size() > 1) rev_hashes.pop_back();
	}

	size_t size() const {
		return hashes.size() - 1;
	}

	/**
	* @brief [l, r) の連続部分列のハッシュ値を返す O(1)
	*/
	int64_t get(int l, int r) {
		assert(0 <= l && l < r && r <= (int)hashes.size() - 1 && "ローリングハッシュのgetは0 <= l < r <= size()でなければなりません");
		// 123の23を取り出したい場合、123 - 1 * base^2
		int64_t hash = (hashes[r] - mul(hashes[l], pow_bases[r - l]) % mod + mod) % mod;
		return hash;
	}
	/**
	* @brief [l, r) の連続部分列の逆方向のハッシュ値を返す O(1)
	*/
	int64_t get_rev(int l, int r) {
		assert(0 <= l && l < r && r <= (int)rev_hashes.size() - 1 && "ローリングハッシュのget_revは0 <= l < r <= size()でなければなりません");
		// 321の32を取り出したい場合、(321 - 1) / base^2 = (321 - 1) * inv_base^2
		int64_t hash = mul((rev_hashes[r] - rev_hashes[l] + mod) % mod, inv_bases[l]);
		return hash;
	}
	/**
	* @brief [l, r) の連続部分列が回文かどうかを判定する O(1)
	*/
	bool is_palindrome(int l, int r) {
		assert(0 <= l && l < r && r <= (int)hashes.size() - 1 && "ローリングハッシュのis_palindromeは0 <= l < r <= size()でなければなりません");
		return get(l, r) == get_rev(l, r);
	}
};



int solve() {
	string s; cin >> s;

	RollingHash<char> rh(s);
	ll mx = 0;
	rep(i, s.size()) {
		if (rh.is_palindrome(s.size() - i - 1, s.size())) {
			chmax(mx, i + 1);
		}
	}

	string s_rev = s;
	reverse(all(s_rev));
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
