#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main() {
    ll n, q;
    cin >> n >> q;
    vvl c(n, vl(26));
    rep(i, n) {
        rep(j, 26) {
            cin >> c[i][j];
        }
    }

    vvl w(q, vl(26, 0));
    rep(i, q) {
        string s;
        cin >> s;
        rep(j, s.size()) {
            w[i][s[j] - 'a']++;
        }
    }

    vvl dp(q + 1, vl(n, 1001001001001));
    rep(i, n) dp[0][i] = 0;

    loop(i, 1, q) { // i番目のワードまで打ったときの
        rep(j, n) { // 直前に使ったのがj番目のキーボードの場合
            rep(k, n) { // k番目のキーボードを使うときのコスト
                ll cost = 0;
                rep(l, 26) {
                    cost += w[i - 1][l] * c[k][l];
                }
                if (j != k && i != 1) cost *= 2;
                dp[i][k] = min(dp[i][k], dp[i - 1][j] + cost);
            }
        }
    }

    ll ans = 1001001001001;
    rep(i, n) {
        ans = min(ans, dp[q][i]);
    }

    cout << ans << endl;
    return 0;
}
