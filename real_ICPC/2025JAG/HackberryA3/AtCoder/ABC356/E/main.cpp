// 調和級数
#include <algorithm>
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




template <typename T> class segtree
{
  public:
    static segtree<T> RangeMinimumQuery(int len) {
        return segtree<T>(len, numeric_limits<T>::max(),
                          [](T a, T b) { return min(a, b); });
    }

    static segtree<T> RangeMaximumQuery(int len) {
        return segtree<T>(len, numeric_limits<T>::lowest(),
                          [](T a, T b) { return max(a, b); });
    }

    static segtree<T> RangeSumQuery(int len) {
        return segtree<T>(len, T(0), [](T a, T b) { return a + b; });
    }
	int length;               // 葉の数

    /**
     * @brief セグメント木のコンストラクタ
     * @param len 配列の長さ
     * @param e 単位元（評価するときの意味のない値。MinQueryの場合、min(x, INF)のINFは意味がない）
     * @param query クエリ関数
     */
    segtree(int len, T e, function<T(T, T)> query)
        : E(e), length(1), _query(std::move(query)) {
        // 要素数を2の冪乗にする
        while (length < len) {
            length <<= 1;
        }
        _data.assign(length * 2 - 1, E);
    }

	/**
	* @remark O(1) 評価しないので、build()を呼ぶこと O(N)
	*/
    T& operator[](size_t i) {
        if (i < 0 || i >= length) throw out_of_range("Index out of range");
        return _data[i + length - 1];
    }

    // 構築 O(N)
    void build() {
        for (int i = length - 2; i >= 0; --i) {
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    // 値を更新 O(log N)
    void update(int i, T value) {
        if (i < 0 || i >= length) throw out_of_range("Index out of range");
        i += length - 1;
        _data[i] = value;
        while (i > 0) {
            i = (i - 1) >> 1;
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    // 区間クエリ [a, b) O(log N)
    T query(int a, int b) const {
		if (a < 0 || b < 0 || a >= length || b > length) throw out_of_range("Index out of range");
		return _querySub(a, b, 0, 0, length);
	}

  private:
    const T E;                // 単位元
    vector<T> _data;          // 完全二分木配列
    function<T(T, T)> _query; // クエリ関数

    // 区間クエリ内部処理
    T _querySub(int a, int b, int k, int l, int r) const {
        if (r <= a || b <= l) { // 完全に範囲外
            return E;
        }
        else if (a <= l && r <= b) { // 完全に範囲内
            return _data[k];
        }
        else { // 一部重なる
            T vl = _querySub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = _querySub(a, b, k * 2 + 2, (l + r) / 2, r);
            return _query(vl, vr);
        }
    }
};

int solve() {
	ll n; cin >> n;
	vll a(n); cin >> a;

	vll cnt(1e6 + 1, 0);
	rep(i, n) {
		cnt[a[i]]++;
	}

	vll sum(1e6 + 2, 0);
	rep(i, 1e6 + 1) {
		sum[i + 1] = sum[i] + cnt[i];
	}

	sort(all(a));

	ll ans = 0;
	loop(y, 1, 1e6) {
		ll now = 0;
		for (ll x = 1; x * y <= 1e6 + 1; ++x) {
			now += (sum[min((ll)1e6 + 1, (x + 1) * y)] - sum[x * y]) * x;
		}
		// 自分自身も入れているので引く
		now -= cnt[y];
		ans += now * cnt[y];
		// 自分と同じ数字（自分自身は外す）の数を足す
		ans += nC2(cnt[y]);
	}

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
