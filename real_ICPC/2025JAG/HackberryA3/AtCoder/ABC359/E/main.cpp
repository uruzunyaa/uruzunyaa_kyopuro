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
    segtree(int len, T e, function<T(T, T)> query) : E(e), _length(1), _query(std::move(query)) {
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
template <typename T> 
class lazy_segtree : public segtree<T>
{
  private:
    // lazyの単位元
    const T ME;
    vector<T> _lazy;

    // lazyを子のlazyに伝播させる関数
    const function<T(T, T)> _merge;
    // lazyをdataに適用する関数
    const function<T(T, T)> _apply;
    // lazyをdataに適用する時に、区間の長さに応じて値を変える関数
    const function<T(T, int)> _proportion;

    void _eval(int k, int len) {
        if (_lazy[k] == ME) return;
        if (k < this->_length - 1) {
            _lazy[k * 2 + 1] = _merge(_lazy[k * 2 + 1], _lazy[k]);
            _lazy[k * 2 + 2] = _merge(_lazy[k * 2 + 2], _lazy[k]);
        }
        this->_data[k] = _apply(this->_data[k], _proportion(_lazy[k], len));
        _lazy[k] = ME;
    }

    void _update_core(int a, int b, T x, int k, int l, int r) {
        _eval(k, r - l);
        if (a <= l && r <= b) {
            _lazy[k] = _merge(_lazy[k], x);
            _eval(k, r - l);
        }
        else if (a < r && l < b) {
            _update_core(a, b, x, k * 2 + 1, l, (l + r) / 2);
            _update_core(a, b, x, k * 2 + 2, (l + r) / 2, r);
            this->_data[k] = this->_query(this->_data[k * 2 + 1], this->_data[k * 2 + 2]);
        }
    }

    T _query_core(int a, int b, int k, int l, int r) {
        _eval(k, r - l);
        if (r <= a || b <= l) { return this->E; }
        else if (a <= l && r <= b) { return this->_data[k]; }
        else {
            T vl = _query_core(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = _query_core(a, b, k * 2 + 2, (l + r) / 2, r);
            return this->_query(vl, vr);
        }
    }

  public:
    /**
     * @brief 遅延セグメント木
     * @param len 配列の長さ
     * @param e 単位元
     * @param queryFunc クエリ関数
     * @param mergeFunc lazyを子のlazyに伝播させる関数
     * @param applyFunc lazyをdataに適用する関数
     * @param proportionFunc
     * lazyをdataに適用する時に、区間の長さに応じて値を変える関数
     * @param me lazyの単位元
     */
    lazy_segtree(int len, T e, function<T(T, T)> queryFunc, function<T(T, T)> mergeFunc, function<T(T, T)> applyFunc, function<T(T, int)> proportionFunc, T me)
        : segtree<T>(len, e, queryFunc), _merge(mergeFunc), _apply(applyFunc), _proportion(proportionFunc), ME(me) {
        _lazy.assign(2 * this->_length - 1, ME);
    }

	/**
	 * @brief ランダムアクセス O(log N)
	 */
	T& operator[](int i) {
		if (i < 0 || i >= this->_length) throw out_of_range("Index out of range");
		query(i, i + 1);
		return this->_data[i + this->_length - 1];
	}

	using segtree<T>::update;
    /**
     * @brief [a, b) 区間更新 O(log N)
     */
    void update(int a, int b, T x) {
        _update_core(a, b, x, 0, 0, this->_length);
    }

    /**
     * @brief 区間クエリ [a, b) O(log N)
     */
    T query(int a, int b) { return _query_core(a, b, 0, 0, this->_length); }

    static lazy_segtree<T> RangeUpdateMinimumQuery(int len, T e = numeric_limits<T>::max()) {
        return lazy_segtree<T>(
            len,
			e,
			[](T a, T b) { return min(a, b); },
            [](T a, T b) { return b; },
			[](T a, T b) { return b; },
            [](T a, int b) { return a; },
			numeric_limits<T>::max());
    }
    static lazy_segtree<T> RangeUpdateMaximumQuery(int len, T e = numeric_limits<T>::min()) {
        return lazy_segtree<T>(
            len,
			e,
			[](T a, T b) { return max(a, b); },
            [](T a, T b) { return b; },
			[](T a, T b) { return b; },
            [](T a, int b) { return a; },
			numeric_limits<T>::min());
    }
    static lazy_segtree<T> RangeUpdateSumQuery(int len, T e = 0) {
        return lazy_segtree<T>(
            len,
			e,
			[](T a, T b) { return a + b; },
			[](T a, T b) { return b; },
            [](T a, T b) { return b; },
			[](T a, int b) { return a * b; },
			0);
    }

    static lazy_segtree<T> RangeAddMinimumQuery(int len, T e = numeric_limits<T>::max()) {
        return lazy_segtree<T>(
            len,
			e,
			[](T a, T b) { return min(a, b); },
            [](T a, T b) { return a + b; },
			[](T a, T b) { return a + b; },
            [](T a, int b) { return a; },
			0);
    }
    static lazy_segtree<T> RangeAddMaximumQuery(int len, T e = numeric_limits<T>::min()) {
        return lazy_segtree<T>(
            len,
			e,
			[](T a, T b) { return max(a, b); },
            [](T a, T b) { return a + b; },
			[](T a, T b) { return a + b; },
            [](T a, int b) { return a; },
			0);
    }
    static lazy_segtree<T> RangeAddSumQuery(int len, T e = 0) {
        return lazy_segtree<T>(
            len,
			e,
			[](T a, T b) { return a + b; },
            [](T a, T b) { return a + b; },
			[](T a, T b) { return a + b; },
            [](T a, int b) { return a * b; },
			0);
    }
};

struct S
{
    ll sum;
    ll minimum;
    ll maximum;

    S() : sum(0), minimum(9009009009009009009LL), maximum(-9009009009009009009LL) {}
    S(ll sum, ll minimum, ll maximum) : sum(sum), minimum(minimum), maximum(maximum) {}

    static S query(S a, S b) {
        return S(a.sum + b.sum, min(a.minimum, b.minimum), max(a.maximum, b.maximum));
    }
    static S update_merge(S a, S b) { return S(b.sum, b.minimum, b.maximum); }
    static S add_merge(S a, S b) {
        return S(a.sum + b.sum, a.minimum + b.minimum, a.maximum + b.maximum);
    }
    static S update_apply(S a, S b) { return S(b.sum, b.minimum, b.maximum); }
    static S add_apply(S a, S b) {
        return S(a.sum + b.sum, a.minimum + b.minimum, a.maximum + b.maximum);
    }
    static S proportion(S a, int b) {
        return S(a.sum * b, a.minimum, a.maximum);
    }

    static S update_identity() { return S(0, INF, -INF); }
    static S add_identity() { return S(0, 0, 0); }

    static lazy_segtree<S> RangeUpdateQuery(int len) {
        return lazy_segtree<S>(len, S(), S::query, S::update_merge, S::update_apply, S::proportion, S::update_identity());
    }

    static lazy_segtree<S> RangeAddQuery(int len) {
        return lazy_segtree<S>(len, S(), S::query, S::add_merge, S::add_apply, S::proportion, S::add_identity());
    }

	bool operator==(const S &rhs) const {
		return sum == rhs.sum && minimum == rhs.minimum && maximum == rhs.maximum;
	}
};

int solve() {
	ll n;
	cin >> n;
	vll a(n);
	cin >> a;

	segtree<ll> wall = segtree<ll>::RangeMaximumQuery(n);
	lazy_segtree<ll> seg = lazy_segtree<ll>::RangeUpdateSumQuery(n + 1);
	rep(i, n) {
		wall[i] = a[i];
	}
	wall.build();

	ll t = 0;
	loop(i, 1, n) {
		ll l = -1, r = i;
		while (r - l > 1) {
			ll m = (l + r) / 2;
			if (wall.query(m, i - 1) >= a[i - 1]) {
				l = m;
			}
			else {
				r = m;
			}
		}

		ll need = (i - r) * a[i - 1];
		ll sum = seg.query(r, i);
		ll diff = need - sum;
		t += diff;
		seg.update(r, i, a[i - 1]);
		cout << t + 1 << " ";
	}

	cout << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
