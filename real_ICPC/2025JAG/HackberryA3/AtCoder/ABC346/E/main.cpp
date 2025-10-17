#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < (n); ++i)
#define loop(i, a, b) for (ll i = (a); i <= (b); ++i)

struct q
{
    ll t, a, x;
};

int main() {
    ll h, w, m;
    cin >> h >> w >> m;
    const ll COL = 2 * 100000 + 1;
    vector<q> query(m);

    vl sum = vl(COL, 0);
    sum[0] = h * w;
    rep(i, m) {
        ll t, a, x;
        cin >> t >> a >> x;
        query[i] = {t, a, x};
    }

    unordered_set<ll> R, C;
    for (ll i = m - 1; i >= 0; --i) {
        ll t = query[i].t;
        ll a = query[i].a;
        ll x = query[i].x;
        if (t == 1) {
            if (R.count(a) != 0) continue;
            sum[x] += w - C.size();
            sum[0] -= w - C.size();
            R.insert(a);
        }
        else {
            if (C.count(a) != 0) continue;
            sum[x] += h - R.size();
            sum[0] -= h - R.size();
            C.insert(a);
        }
    }

    ll k = 0;
    string res = "";
    rep(i, COL) {
        if (sum[i] > 0) {
            k++;
            res += to_string(i) + " " + to_string(sum[i]) + "\n";
        }
    }
    cout << k << endl;
	cout << res;

    return 0;
}