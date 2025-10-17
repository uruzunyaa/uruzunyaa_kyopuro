#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

ll binary_search(const vector<ll>& a){
    return 0;
}

int main() {
    ll n, q, L, R;
    cin >> n >> q >> L >> R;
    vector<ll> a(n);
    rep(i, n){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<ll> mode(q), x(q), s(q), t(q);
    rep(i, q){
        cin >> mode[i] >> x[i] >> s[i] >> t[i];
    }
    // 答えがL以上になる最小のiを見つける
    ll left = -1, right = n;
    while(right - left > 1){
        ll mid = (left + right) / 2;

        ll ans = a[mid];
        if (0 <= mid && mid < n) {
            rep(i, q){
                if(mode[i] == 1){
                    if(ans < x[i])continue;
                    ans = (ans + s[i]) * t[i];
                }else if(mode[i] == 2){
                    if(ans > x[i])continue;
                    ans = (ans - s[i]) / t[i];
                }
            }
        }
        else {
            if (mid == n) ans = (1LL << 63) + 1;
        }

        if(ans < L || mid == -1){
            left = mid;
        }else{
            right = mid;
        }
    }
    ll leftans = right;

    // 答えがR以下になる最大のiを見つける
    left = -1, right = n;
    while(right - left > 1){
        ll mid = (left + right) / 2;

        ll ans = a[mid];
        if (0 <= mid && mid < n) {
            rep(i, q){
                if(mode[i] == 1){
                    if(ans < x[i])continue;
                    ans = (ans + s[i]) * t[i];
                }else if(mode[i] == 2){
                    if(ans > x[i])continue;
                    ans = (ans - s[i]) / t[i];
                }
            }
        }
        else {
            if (mid == n) ans = (1LL << 63) + 1;
        }

        if(ans <= R || mid == -1){
            left = mid;
        }else{
            right = mid;
        }
    }
    ll rightans = left;

    cout << rightans - leftans + 1 << endl;
    return 0;
}