#include <bits/stdc++.h>
#include <iostream>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i <= (b); ++i)

int main() {
    int n, k;
    cin >> n >> k;
    vll car(k);
    vll sum(k);

    rep(i, n) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        r--;
        if (t == 0) {
            ll x;
            cin >> x;

            loop(j, l, r) {
                car[j] += x;
                if (0 <= x) sum[j] += x;
            }
        }
        else {
            ll ans_cnt = 0, ans_sum = 0;
            loop(j, l, r) {
                ans_cnt += car[j];
                ans_sum += sum[j];
            }
            cout << ans_cnt << " " << ans_sum << endl;
        }
    }

    int L, R;
    cin >> L >> R;
    L--;
    R--;
    ll ans_cnt = 0, ans_sum = 0;
    loop(i, L, R) {
        ans_cnt += car[i];
        ans_sum += sum[i];
    }

    cout << ans_cnt << " " << ans_sum << endl;

    return 0;
}