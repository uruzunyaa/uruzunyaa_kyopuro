#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)

template <typename T>
class segtree {
  protected:
    const T E;
    vector<T> _data;
    const function<T(T,T)> _query;
    int _length;

    T _query_sub(int a, int b, int k, int l, int r) const {
        if (r <= a || b <= l) {
            return E;
        }
        else if (a <= l && r <= b) {
            return _data[k];
        }
        else {
            T vl = _query_sub(a, b, k * 2 + 1, l , (l + r) / 2);
            T vr = _query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return _query(vl, vr);
        }
    }

    public:
    segtree(int len, T e, function<T(T,T)> query) : E(e), _query(move(query)), _length(1) {
        while (_length < len) {
            _length <<= 1;
        }
        _data.assign(_length * 2 - 1, E);
    }

    size_t size() const {return _length;}

    T &operator[](size_t i) {
        if (i < 0 || i >= _length) throw out_of_range("Index out of range");
        return _data[i + _length - 1];
    }

    void build() {
        for (int i = _length - 2; i >= 0; --i) {
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    void update(int i, T value) {
        if (i < 0 || i >= _length) throw out_of_range("Index out of range");
        i += _length - 1;
        _data[i] = value;
        while (i > 0) {
            i = (i - 1) >> 1;
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    T query(int a, int b) const {
        if (a < 0 || b < 0 || a > _length || b > _length) throw out_of_range("Index out of range");
        return _query_sub(a, b, 0, 0, _length);
    }
};

struct Data {
    vector<pair<int, int>> cnt;
    int size;

    Data() : cnt(vector<pair<int, int>>()), size(0) {}
    Data(vector<pair<int, int>> cnt, int size) : cnt(cnt), size(size) {}
};

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<vector<int>> divs(1e6 + 1);
    for (int i = 2; i <= 1e6; ++i) {
        for (int j = i; j <= 1e6; j += i) {
            divs[j].push_back(i);
        }
    }

    segtree<Data> seg(n, Data(), [](Data a, Data b) -> Data {
        int nsize = a.size + b.size;
        sort(a.cnt.rbegin(), a.cnt.rend());
        sort(b.cnt.rbegin(), b.cnt.rend());
        
        vector<pair<int, int>> res;
        while (a.cnt.size() > 0 || b.cnt.size() > 0) {
            auto [aval, acnt] = a.cnt.size() > 0 ? a.cnt.back() : make_pair(2002002002, 0);
            auto [bval, bcnt] = b.cnt.size() > 0 ? b.cnt.back() : make_pair(2002002002, 0);
            if (aval == bval) {
                if (nsize - 2 <= acnt + bcnt) res.push_back({aval, acnt + bcnt});
                a.cnt.pop_back();
                b.cnt.pop_back();
            }
            else if (aval < bval) {
                if (nsize - 2 <= acnt) res.push_back({aval, acnt});
                a.cnt.pop_back();
            }
            else {
                if (nsize - 2 <= bcnt) res.push_back({bval, bcnt});
                b.cnt.pop_back();
            }
        }

        return Data(res, nsize);
    });

    rep(i, n) {
        vector<pair<int, int>> cnt;
        for (ll v : divs[a[i]]) {
            cnt.push_back({v, 1});
        }
        seg[i] = Data(cnt, 1);
    }
    seg.build();

    rep(i, m) {
        char t; cin >> t;
        if (t == 'U') {
            ll j, x; cin >> j >> x;
            --j;

            vector<pair<int, int>> cnt;
            for (ll v : divs[x]) {
                cnt.push_back({v, 1});
            }
            seg.update(j, {cnt, 1});
        }
        else {
            ll l, r, k; cin >> l >> r >> k;
            --l;
            Data d = seg.query(l, r);

            long long ans = 1;
            for (auto [v, c] : d.cnt) {
                if (c < d.size - k) continue;
                ans = lcm(ans, (long long)v);
            }
            cout << ans << "\n";
        }
    }

    return 0;
}