#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n, t;
    cin >> n >> t;
    vector<ll> health(n);
    rep(i, n){
        cin >> health[i];
    }
    ll offset = 0;
    ll nowmax = 0;
    rep(i, n){
        nowmax = max(nowmax,health[i]);
        ll kiriage = (((t - offset) * 2 + 1) + (nowmax * 2) - 1) / (nowmax * 2);
        ll kirisute = ((t - offset) * 2 + 1) / (nowmax * 2);

        ll temp = ((t - offset) * 2 + 1) - kirisute * nowmax * 2;
        if(health[i] * 2 <= temp)cout << max(1LL,kiriage + 1) << endl;
        else cout << max(1LL,kiriage) << endl;

        // cout << (((t - offset) * 2 + 1) + (nowmax * 2) - 1) / (nowmax * 2)  << endl;
        offset += health[i];
    }
}