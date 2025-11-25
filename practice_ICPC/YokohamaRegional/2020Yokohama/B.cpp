#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)
ll INF = 1LL << 60;

int main() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    vector<ll> ruisekia(n), ruisekib(m);
    rep(i, n){
        cin >> a[i];
    }
    rep(i, m){
        cin >> b[i];
    }
    ll now = INF;
    for(ll i = n - 1; i >= 0; i--){
        if(a[i] != 0){
            now = a[i];
        }
        ruisekia[i] = now;
    }
    now = INF;
    for(ll i = m - 1; i >= 0; i--){
        if(b[i] != 0){
            now = b[i];
        }
        ruisekib[i] = now;
    }

    ll idxa = 0, idxb = 0;
    for(ll i = 1; i <= n + m; i++){
        if(idxa == n){
            b[idxb] = i;
            idxb++;
        }else if(idxb == m){
            a[idxa] = i;
            idxa++;
        }
        else if(a[idxa] == i){
            idxa++;
        }
        else if(b[idxb] == i){
            idxb++;
        }
        else if(ruisekia[idxa] < ruisekib[idxb]){
            if(a[idxa] != 0){
                b[idxb] = i;
                idxb++;
            }else{
                a[idxa] = i;
                idxa++;
            }
        }else{
            if(b[idxb] != 0){
                a[idxa] = i;
                idxa++;
            }else{
                b[idxb] = i;
                idxb++;
            }
        }
    }
    rep(i, n){
        cout << a[i];
        if(i != n - 1)cout << " ";
        else cout << '\n';
    }
    rep(i, m){
        cout << b[i];
        if(i != m - 1)cout << " ";
        else cout << '\n';
    }
    return 0;
}