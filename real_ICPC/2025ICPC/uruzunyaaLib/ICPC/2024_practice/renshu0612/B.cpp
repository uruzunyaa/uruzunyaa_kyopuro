// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (long long i = 0; i < n; i++)
#define loop(i, m, n) for (long long i = m; i <= n; i++)
#define range(value, range) for (const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a)                                                                \
    rep(ii, a.size()) { cout << a[ii] << " "; }                                \
    cout << endl;
#define vvdbg(a)                                                               \
    rep(ii, a.size()) {                                                        \
        rep(jj, a[ii].size()) { cout << a[ii][jj] << " "; }                    \
        cout << endl;                                                          \
    }
#define inf 4000000000000000000LL
#define mod 998244353

ll solve() {
    ll k;
    cin >> k;
    if (k == 0) return 1;

    string s;
    cin >> s;

    vvl dp(k, vl(s.size() + 1, -inf));
    dp[0][0] = 0;
    loop(j, 1, s.size()) {
		rep(i, k) {
            ll now = dp[(i + 1) % k][j - 1];
            ll pow10 = 1;
            rep(exp, i) pow10 *= 10;
            now += pow10 * (s[j - 1] - '0');

            dp[i][j] = max(now, dp[i][j - 1]);
        }
    }

    cout << dp[0][s.size()] << endl;

    return 0;
}

int main() {
    while (1) {
        if (solve() == 1) break;
    }
    return 0;
}
