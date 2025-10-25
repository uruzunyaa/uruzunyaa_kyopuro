#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
#define vll vector<ll>
#define vvll vector<vll>
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n; cin >> n;
    vll a(n); rep(i, n) cin >> a[i];

    vector<vector<PLL>> g(n);
    rep(s, n) {
        priority_queue<ll> small;
        priority_queue<ll, vector<ll>, greater<ll>> big;
        ll smallSum = 0, bigSum = 0, center = a[s];

        loop(i, s + 1, n - 1) {
            if (center != INF) {
                ll x = a[i], y = center;
                if (y < x) swap(x, y);
                small.push(x);
                smallSum += x;
                big.push(y);
                bigSum += y;
                center = INF;
            }
            else {
                if (a[i] < small.top()) {
                    small.push(a[i]);
                    smallSum += a[i];
                    center = small.top();
                    smallSum -= small.top();
                    small.pop();
                }
                else if (big.top() < a[i]) {
                    big.push(a[i]);
                    bigSum += a[i];
                    center = big.top();
                    bigSum -= big.top();
                    big.pop();
                }
                else {
                    center = a[i];
                }
            }
            g[s].push_back({i, bigSum - smallSum});
        }
    }

    vector<ll> dp(n, INF);
    dp[0] = 0;
    rep(i, n) {
        for (auto [to, cost] : g[i]) {
            dp[to] = min(dp[to], dp[i] + cost);
        }
    }

    cout << dp[n - 1] << endl;
    return 0;
}