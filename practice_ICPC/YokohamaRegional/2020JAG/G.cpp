#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n-1; i >=0; i--)
#define loop(i,m,n)for(ll i=m;i<=n;i++)
#define vll vector<ll>
#define vvll vector<vll>

int main() {
    string s; cin >> s;
    ll a; cin >> a;

    ll l = (s.size() + 1) / 2;
    ll r = s.size() / 2;
    vector<map<ll, ll>> cnt(19);
    rep(bit, 1LL << l) {
        string i = "";
        ll res = 0;

        bool ok = true;
        rep(j, l) {
            if (bit & (1LL << j)) {
                if (s[j] == '+') {
                    if (i == "") {
                        ok = false;
                        break;
                    }

                    res += stoll(i);
                    i = "";
                }
                else {
                    i += s[j];
                }
            }
        }

        if (!ok) continue;

        // iが空で終わっていたら+で終わっている
        if (i == "") {
            loop(j, 1, cnt.size() - 1) {
                cnt[j][res]++;
            }
        }
        else {
            ll now = stoll(i);
            rep(j, cnt.size()) {
                cnt[j][res + now]++;
                if (LLONG_MAX / 10 <= now) break;
                now *= 10;
            }
        }
    }



    ll ans = 0;
    rep(bit, 1LL << r) {
        string i = "";
        ll res = 0;

        bool ok = true;
        for (ll j = r - 1; j >= 0; j--) {
            if (bit & (1LL << j)) {
                if (s[l + j] == '+') {
                    if (i == "") {
                        ok = false;
                        break;
                    }

                    reverse(i.begin(), i.end());
                    res += stoll(i);
                    i = "";
                }
                else {
                    i += s[l + j];
                }
            }
        }
        if (!ok) continue;

        // 最後iに残っていた桁数がずれる数
        ll mv = i.size();
        reverse(i.begin(), i.end());
        if (mv != 0) res += stoll(i);
        ans += cnt[mv][a - res];
    }

    cout << ans << endl;
    return 0;
}