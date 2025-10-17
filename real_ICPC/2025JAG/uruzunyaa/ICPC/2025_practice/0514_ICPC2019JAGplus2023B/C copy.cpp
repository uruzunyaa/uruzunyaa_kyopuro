#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    while(1){
        ll n;
        cin >> n;
        if(n == 0)break;
        ll a,b,c,d;
        cin >> a >> b >> c >> d;
        vector<ll> x(n+1),y(n+1);
        rep(i,n+1){
            cin >> x[i] >> y[i];
            //x[i]--;
            //y[i]--;
        }
        vector<vector<bool>> poison(100,vector<bool>(100,true));
        for(int i = b; i <= d; i++){
            for(int j = a; j <= c; j++){
                poison[i-1][j-1] = false;
            }
        }
        vector<ll> cost_to_no_poison(n + 1, 10000);
        rep(k, n + 1){
            for(int i = b; i <= d; i++){
                for(int j = a; j <= c; j++){
                    ll dist = abs(y[k] - i) + abs(x[k] - j);
                    cost_to_no_poison[k] = min(cost_to_no_poison[k],dist);
                }
            }
        }
        ll ans = 0;
        //rep(i, n + 1){
            //cout << cost_to_no_poison[i] << endl;
        //}
        
        rep(i, n){
             ll cost1 = max(0LL,cost_to_no_poison[i] - 1) + cost_to_no_poison[i + 1];
            //  if(cost1 < 0)cost1 = 0;
             ll cost2 = abs(y[i] - y[i+1]) + abs(x[i] - x[i + 1]);
             ans += min(cost1,cost2);
        }
        cout << ans << endl;
    }
    return 0;
}
