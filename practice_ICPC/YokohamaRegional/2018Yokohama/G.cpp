#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; i++)
#define vll vector<long long>
constexpr ll INF = 9009009009009009009LL;

template <typename T>
class segtree
{
    protected:
    const T E;
    vector<T> _data;
    const function<T(T, T)> _query;
    int _length;

    T _query_sub(int a, int b, int k, int l, int r) const {
        if(r <= a || b <= l){
            return E;
        }
        else if (a <= l && r <= b){
            return _data[k];
        }
        else{
            T vl = _query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = _query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return _query(vl, vr);
        }
    }

    public:
    segtree(int len, T e, function<T(T, T)> query) : E(e), _query(std::move(query)), _length(1) {
        while(_length < len){
            _length <<= 1;
        }
        _data.assign(_length * 2 - 1, E);
    }

    size_t size() const {return _length;}

    T &operator[](size_t i){
        if (i < 0 || i >= _length) throw out_of_range("Index out of range");
        return _data[i + _length - 1];
    }

    void build(){
        for (int i = _length - 2; i >= 0; --i){
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    void update(int i, T value){
        if (i < 0 || i >= _length) throw out_of_range("Index out of range");
        i += _length - 1;
        _data[i] = value;
        while(i > 0){
            i = (i - 1) >> 1;
            _data[i] = _query(_data[i * 2 + 1], _data[i * 2 + 2]);
        }
    }

    T query(int a, int b) const {
        if(a < 0 || b < 0 || a >= _length || b > _length)throw out_of_range("Index out of range");
        return _query_sub(a, b, 0, 0, _length);
    }

    static segtree<T> RangeSumQuery(ll len, T e = 0) {
        return segtree<T>(len, e, [](T a, T b) { return a + b; });
    }
};

ll inversion_number(vll &v) {
    int n = v.size();
    if(n == 1) return 0;
    vll v1(v.begin(),v.begin() + n / 2);
    vll v2(v.begin() + n / 2, v.end());
    ll res = inversion_number(v1) + inversion_number(v2);
    int p = 0, q = 0;
    rep(i, n){
        if(q == v2.size() || (p < v1.size() && v1[p] <= v2[q])){
            v[i] = v1[p++];
        }else{
            v[i] = v2[q++];
            res += v1.size() - p;
        }
    }
    return res;
}



int main(){
    ll n; cin >> n;
    vll a(n);
    rep(i, n) cin >> a[i];

    map<ll, vector<ll>> index;
    rep(i, n) index[a[i]].push_back(i);

    segtree<ll> seg = segtree<ll>::RangeSumQuery(n);
    rep(i, n) {
        seg[i] = 1;
    }
    seg.build();

    ll ans = 0;
    for (auto [_, idxs] : index) {
        for (ll i : idxs) {
            seg.update(i, 0);
        }
        for (ll i : idxs) {
            ll l = seg.query(0, i);
            ll r = seg.query(i, n);
            ans += min(l, r);
        }
    }

    cout << ans << "\n";

    return 0;
}