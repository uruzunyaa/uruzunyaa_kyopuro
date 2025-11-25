#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i,m, n) for (ll i = m; i <= n; ++i)
const ll mod = 998244353;
const ll INF = 1LL << 60;

ll power(ll A, ll B) {
    ll result = 1;
    rep(i, B){
        result *= A;
    }
    return result;
}

ll logax(ll a, ll x){
    if(x <= 1)return 0;
    ll result = 1;
    ll power = 1;
    while(power < (x + a - 1) / a){
        power *= a;
        result++;
    }
    return result;

}

template<typename T>
struct SegTree{
    ll size;
    ll tall;
    vector<T> data;
    function<T(T, T)> p;
    SegTree(vector<T> a, function<T(T, T)> put, T d) : data(power(2, logax(2, a.size()) + 1)) {
        size = data.size() / 2;
        tall = logax(2, size) + 1;
        p = put;
        ll tmp = size;
        data = vector<T>(size * 2, d);
        while(tmp != 0){
            if(tmp == size)rep(i, a.size())data[tmp + i] = a[i];
            else rep(i, tmp) data[tmp + i] = p(data[2 * (tmp + i)], data[2 * (tmp + i) + 1]);
            tmp /= 2;
        }
    }

    void update(ll t, T x){
        t += size;
        while(t != 0){
            if(t >= size) data[t] = x;
            else data[t] = p(data[2 * t], data[2 * t + 1]);
            t /= 2;
        }
    }

    T get(ll l, ll r){
        l = max(0LL, l);
        r = min(r, size - 1);
        r++;
        T ans = data[0];
        ll pos = l + size;
        ll wid = 1;
        while(l + (wid * 2) <= r){
            while(l % (wid * 2) == 0 && l + (wid * 2) <= r)pos /= 2, wid *= 2;
            ans = p(ans, data[pos]);
            pos++;
            l += wid;
        }
        while(l!=r){
            while(l + wid > r)pos *= 2, wid/= 2;
            ans = p(ans, data[pos]);
            pos++;
            l += wid;
        }
        return ans;
    }
}

int main() {
    return 0;
}