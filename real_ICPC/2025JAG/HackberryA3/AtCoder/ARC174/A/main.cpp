#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i <= (b); ++i)

int main() {
    ll n, c;
    cin >> n >> c;
    vl a(n);
    rep(i, n) cin >> a[i];

    int l = n, r = n;
    int tl = -1;
    ll sumMax = 0;
    ll sum = 0;
    rep(i, n) {
        ll x = sum + a[i] * c;
        ll y = a[i] * c;

        if (y >= x) {
            tl = i;
            sum = y;
            if (sumMax < sum) {
                sumMax = sum;
                l = tl;
                r = i;
                tl = -1;
            }
        }
        else {
            sum = x;
            if (sumMax < sum) {
                sumMax = sum;
                l = tl == -1 ? l : tl;
                tl = -1;
                r = i;
            }
        }
    }

    ll ans = 0;
    rep(i, n) { ans += a[i] * (l <= i && i <= r ? c : 1); }

    cout << (c == 0 && ans < 0 ? 0 : ans) << endl;

    return 0;
}