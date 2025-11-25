#include <bits/stdc++.h>
using namespace std;
using ll = int;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll INF = 2002002002;

template <typename T>
class segtree
{
public:
    T E;                              // const を外した
    vector<T> _data;
    function<T(T, T)> _query;         // const を外した
    int _length;                      // const を外した

    T _query_sub(int a, int b, int k, int l, int r) const {
        if (r <= a || b <= l) {
            return E;
        } else if (a <= l && r <= b) {
            return _data[k];
        } else {
            T vl = _query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = _query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return _query(vl, vr);
        }
    }

    segtree() {}
    segtree(int len, T e, function<T(T, T)> query)
        : E(e), _query(std::move(query)), _length(1)
    {
        while (_length < len) {
            _length <<= 1;
        }
        _data.assign(_length * 2 - 1, E);
    }

    // ★★★ コピー代入演算子 ★★★
    segtree& operator=(const segtree& other) {
        if (this == &other) return *this;

        this->E = other.E;
        this->_query = other._query;
        this->_length = other._length;
        this->_data = other._data;

        return *this;
    }

    // ★★★ ムーブ代入演算子（任意） ★★★
    segtree& operator=(segtree&& other) noexcept {
        if (this == &other) return *this;

        this->E = std::move(other.E);
        this->_query = std::move(other._query);
        this->_length = other._length;
        this->_data = std::move(other._data);

        return *this;
    }

    size_t size() const { return _length; }

    T& operator[](size_t i) {
        if (i < 0 || i >= _length) {
            while (true) {}
        }
        return _data[i + _length - 1];
    }

    void build() {
        for (int i = _length - 2; i >= 0; --i) {
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    void update(int i, T value) {
        if (i < 0 || i >= _length) {
            while (true) {}
        }
        i += _length - 1;
        _data[i] = value;
        while (i > 0) {
            i = (i - 1) >> 1;
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    T query(int a, int b) const {
        if (a < 0 || b < 0 || a >= _length || b > _length) {
            while (true) {}
        }
        return _query_sub(a, b, 0, 0, _length);
    }

    static segtree<T> RangeMaximumQuery(int len, T e = numeric_limits<T>::min()) {
        return segtree<T>(len, e, [](T a, T b) { return max(a, b); });
    }
};

// segtree<PLL> seg;
// int ans = 0;
// int dfs(int l, int r, int depth) {
//     if (r - l == 1) {
//         ans = max(ans, depth);
//         return 1;
//     }
//     if (r <= l) {
//         return 0;
//     }
//     // 最大を取得
//     int i = seg.query(l, r).second;

//     // 左
//     int left = dfs(l, i, depth + 1);
//     int right = dfs(i + 1, r, depth + 1);

//     ans = max(ans, left + right + depth);
//     return max(left, right) + 1;
// }

int main() {
    ll n; cin >> n;
    vector<ll> h(n);
    rep(i, n) {
        cin >> h[i];
    }

    segtree<PLL> seg = segtree<PLL>(n, {-INF, -INF}, [](PLL a, PLL b) { return max(a, b); });
    rep(i, n) {
        seg[i] = {h[i], i};
    }
    seg.build();

    ll ans = 0;
    auto dfs = [&](auto dfs, ll l, ll r, ll depth) -> ll {
        if (r - l == 1) {
            ans = max(ans, depth);
            return 1;
        }
        if (r <= l) {
            return 0;
        }
        // 最大を取得
        ll i = seg.query(l, r).second;

        // 左
        ll left = dfs(dfs, l, i, depth + 1);
        ll right = dfs(dfs, i + 1, r, depth + 1);

        ans = max(ans, left + right + depth);
        return max(left, right) + 1;
    };
    dfs(dfs, 0, n, 0);
    // dfs(0, n, 0);

    cout << ans << endl;
    return 0;
}