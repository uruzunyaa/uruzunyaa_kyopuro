#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

int solve() {
    ll n, m;
    cin >> n >> m;
	if(n == 0 && m == 0){return 1;}
    vector<ll> d(n),p(n);
    vector<pair<ll,ll>> d_p(n);
    rep(i, n){
        cin >> d[i] >> p[i];
        d_p[i].first = p[i];
        d_p[i].second = d[i];
    }
    sort(d_p.rbegin(),d_p.rend());
    ll ans = 0;
    rep(i, n){
        if(d_p[i].second <= m){
            m -= d_p[i].second;
            d_p[i].second = 0;
        }else{
            d_p[i].second -= m;
            m = 0;
            break;
        }
    }
    rep(i, n){
        ans += d_p[i].first * d_p[i].second;
    }
    cout << ans << endl;
    return 0;
}
int main() {
    while(solve() == 0);
    return 0;
}