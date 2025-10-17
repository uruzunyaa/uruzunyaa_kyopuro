#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= (ll)b; ++i)

int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};
int main(){
    ll n, c, p, q;
    cin >> n >> c >> p >> q;
    string s;
    cin >> s;

    ll ans = 0;
    ll last = 0;
    vector<pair<ll, ll>> sum(n + 1, {0, 0});
    loop(i, 1, n)
    {
        sum[i] = {sum[i - 1].first + (s[i - 1] == 'Y' ? 1 : 0), sum[i - 1].second + 1};
        if (i - c < 0) continue;

        loop(j, max(last, i - 2 * c), i - c) {
            ll a = (sum[i].first - sum[j].first) * q;
            ll b = p * (sum[i].second - sum[j].second);
            if (b <= a) {
                ans++;
                last = i;
                break;
            }
        }
    }

    cout << ans << endl;
    return 0;
}