#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main(){
    ll n, u, l, d;
    cin >> n >> u >> l >> d;
    queue<ll> q;
    ll cntu = 0, cntl = 0;
    ll ans = 0;
    bool alert = false;
    rep(i, n){
        ll x;
        cin >> x;
        q.push(x);
        if(x >= u)cntu++;
        if(x <= l)cntl++;
        if(q.size() > d){
            if(q.front() >= u)cntu--;
            if(q.front() <= l)cntl--;
            q.pop();
        }
        if(cntu == d){
            if(!alert){
                alert = true;
                ans++;
            }
        }
        if(cntl == d){
            alert = false;
        }
    }
    cout << ans << endl;
    return 0;
}