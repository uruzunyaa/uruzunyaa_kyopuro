#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    while(1){
        ll t,n;
        cin >> t >> n;
        if(t == 0)break;
        set<pair<ll,ll>> obstacle;
        set<pair<ll,ll>> cnt;
        queue<pair<pair<ll,ll>,ll>> q;
        rep(i, n){
            ll x,y;
            cin >> x >> y;
            obstacle.insert({x,y});
        }
        ll startx,starty;
        cin >> startx >> starty;
        q.push({{startx,starty},0ll});
        cnt.insert({startx,starty});
        while(!q.empty()){
            ll nowx = q.front().first.first;
            ll nowy = q.front().first.second;
            ll nowcost = q.front().second;
            q.pop();
            if(nowcost >= t)continue;
            for(ll i = -1; i <= 1; i++){
                for(ll j = -1; j <= 1; j++){
                    if(i == 1 && j == -1)continue;
                    if(j == 1 && i == -1)continue;
                    ll nx = nowx + i;
                    ll ny = nowy + j;
                    if(!cnt.count({nx,ny}) && !obstacle.count({nx,ny})){
                        cnt.insert({nx,ny});
                        q.push({{nx,ny},nowcost + 1});
                    }
                }
            }
        }
        cout << cnt.size() << endl;
    }
    return 0;
}