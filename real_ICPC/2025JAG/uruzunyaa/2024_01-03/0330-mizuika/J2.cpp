#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define mod 998244353

int main() {
    ll n, k;
    cin >> n >> k;
    vvl dp(n + 1, vl(k + 1, 0));

    // 初期条件
    fill(dp[n].begin(), dp[n].end(), 1); // 最後の数字であれば、どの数字でも通りは1

    // ボトムアップでDPテーブルを構築
    for(ll s = n - 1; s >= 1; --s) {
        if(s % 2 == 1) {
            // 次の数字は上に上がる
            for(ll m = k; m >= 1; --m) {
                dp[s][m] = dp[s][m+1] + dp[s+1][m+1];
                dp[s][m] %= mod;
            }
        } else {
            // 次の数字は下に下がる
            for(ll m = 1; m <= k; ++m) {
                dp[s][m] = dp[s][m-1] + dp[s+1][m-1];
                dp[s][m] %= mod;
            }
        }
    }

    ll ans = 0;
    for(ll i = 1; i <= k; ++i) {
        ans += dp[1][i];
        ans %= mod;
    }

    ans *= 2;
    ans %= mod;
    cout << ans << endl;
    return 0;
}
