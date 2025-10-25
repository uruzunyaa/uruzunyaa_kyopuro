#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n, L; cin >> n >> L;
    vector<PLL> lr(n);
    rep(i, n) {
        ll l, r; cin >> l >> r;
        lr[i] = {l, r};
    }
    
    // x
    priority_queue<PLL, vector<PLL>, greater<PLL>> lq;
    priority_queue<ll> rq;
    rep(i, n) {
        lq.push({lr[i].first, lr[i].second});
    }
    
    ll now = 0;
    ll x = 0;
    while (now < L) {
        while (!lq.empty() && lq.top().first <= now) {
            rq.push(lq.top().second);
            lq.pop();
        }
        
        now = rq.top();
        x++;
        rq.pop();
    }
    cout << x << " ";

    // y
    map<ll, ll> mp;
    rep(i, n) {
        mp[lr[i].first] = 0;
        mp[lr[i].second] = 0;
    }
    auto it = mp.begin();
    for (ll i = 0; it != mp.end(); ++it, ++i) {
        it->second = i;
    }

    vl imos(mp.rbegin()->second + 1, 0);
    rep(i, n) {
        imos[mp[lr[i].first]] += 1;
        imos[mp[lr[i].second]] -= 1;
    }

    ll mn = INF;
    ll sum = 0;
    rep(i, mp.rbegin()->second) {
        sum += imos[i];
        mn = min(mn, sum);
    }

    cout << n - mn + 1 << endl;
}