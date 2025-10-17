#include <bits/stdc++.h>
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
class segtree
{
  protected:
    const T E;                      // 単位元
    vector<T> _data;                // 完全二分木配列
    const function<T(T, T)> _query; // クエリ関数
    int _length;                    // 葉の数

    T _query_sub(int a, int b, int k, int l, int r) const {
        if (r <= a || b <= l) { // 完全に範囲外
            return E;
        }
        else if (a <= l && r <= b) { // 完全に範囲内
            return _data[k];
        }
        else { // 一部重なる
            T vl = _query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = _query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return _query(vl, vr);
        }
    }

  public:
    /**
     * @brief セグメント木
     * @param len 配列の長さ
     * @param e 単位元（評価するときの意味のない値。MinQueryの場合、min(x,
     * INF)のINFは意味がない）
     * @param query クエリ関数
     */
    segtree(int len, T e, function<T(T, T)> query) : E(e), _query(std::move(query)), _length(1) {
        // 要素数を2の冪乗にする
        while (_length < len) {
            _length <<= 1;
        }
        _data.assign(_length * 2 - 1, E);
    }

    size_t size() const { return _length; }

    /**
     * @remark O(1) 評価しないので、build()を呼ぶこと O(N)
     */
    T &operator[](size_t i) {
        if (i < 0 || i >= _length) throw out_of_range("Index out of range");
        return _data[i + _length - 1];
    }

    /**
     * @brief 構築 O(N)
     */
    void build() {
        for (int i = _length - 2; i >= 0; --i) {
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    /**
     * @brief 更新 O(log N)
     */
    void update(int i, T value) {
        if (i < 0 || i >= _length) throw out_of_range("Index out of range");
        i += _length - 1;
        _data[i] = value;
        while (i > 0) {
            i = (i - 1) >> 1;
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    /**
     * @brief 区間クエリ [a, b) O(log N)
     */
    T query(int a, int b) const {
        if (a < 0 || b < 0 || a >= _length || b > _length)
            throw out_of_range("Index out of range");
        return _query_sub(a, b, 0, 0, _length);
    }

    static segtree<T> RangeMinimumQuery(int len,
                                        T e = numeric_limits<T>::max()) {
        return segtree<T>(len, e, [](T a, T b) { return min(a, b); });
    }

    static segtree<T> RangeMaximumQuery(int len,
                                        T e = numeric_limits<T>::min()) {
        return segtree<T>(len, e, [](T a, T b) { return max(a, b); });
    }

    static segtree<T> RangeSumQuery(int len, T e = 0) {
        return segtree<T>(len, e, [](T a, T b) { return a + b; });
    }

    static segtree<T> RangeProductQuery(int len, T e = 1) {
        return segtree<T>(len, e, [](T a, T b) { return a * b; });
    }

    static segtree<T> RangeXorQuery(int len, T e = 0) {
        return segtree<T>(len, e, [](T a, T b) { return a ^ b; });
    }
};

int solve() {
	ll n; cin >> n;
	vll c(n, 0);
	vll a(n, 0);
	loop(i, 1, n - 1) {
		ll ci; cin >> ci;
		c[i] = ci;
	}
	loop(i, 1, n - 1) {
		ll ai; cin >> ai;
		a[i] = ai;
	}

	segtree<PLL> seg(n, {INF, INF}, [&](PLL left, PLL right) {
		if (left.second == INF) return right;
		if (right.second == INF) return left;

		if (a[left.second] == 0 && a[right.second] != 0) {
			return right;
		}
		else if (a[left.second] != 0 && a[right.second] == 0) {
			return left;
		}
		else {
			if (left.second - c[left.second] < right.second - c[right.second]) {
				return left;
			}
			else if (left.second - c[left.second] > right.second - c[right.second]) {
				return right;
			}
			else {
				return left.first < right.first ? left : right;
			}
		}
	});

	vector<PLL> dp(n);
	dp[0] = {0, 0};
	loop(i, 1, n - 1) {
		if (i - c[i] <= 0) {
			seg.update(i, {1, i});
			dp[i] = {1, 0};
			continue;
		}

		PLL p = seg.query(i - c[i], i);
		seg.update(i, {p.first + 1, i});
		dp[i] = {p.first + 1, p.second};
	}

	vector<bool> checked(n, false);
	ll ans = 0;
	for (ll i = n - 1; i > 0; --i) {
		if (checked[i]) continue;
		if (a[i] == 0) continue;

		ll same = 0;
		ll j = dp[i].second;
		while (j != 0) {
			if (checked[j]) {
				same = dp[j].first;
				break;
			}
			checked[j] = true;
			j = dp[j].second;
		}

		ans += dp[i].first - same;
	}

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
