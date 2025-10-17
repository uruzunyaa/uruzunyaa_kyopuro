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
            x[i]--;
            y[i]--;
        }
        vector<vector<bool>> poison(100,vector<bool>(100,true));
        for(int i = b; i <= d; i++){
            for(int j = a; j <= c; j++){
                poison[i-1][j-1] = false;
            }
        }
        vector<ll> cost_to_no_poison(n + 1, 0);
        ll dx[] = {-1,0,0,1};
        ll dy[] = {0,1,-1,0};
        rep(i, n + 1){
            queue<pair<pair<ll,ll>,ll>> q;
            vector<vector<bool>> visited(100,vector<bool>(100,false));
            q.push({{x[i],y[i]},0});
            visited[y[i]][x[i]] = true;
            bool flag = false;
            while(!q.empty() && !flag){
                ll tx = q.front().first.first;
                ll ty = q.front().first.second;
                ll nowcost = q.front().second;
                q.pop();
                rep(i, 4){
                    ll nx = tx + dx[i];
                    ll ny = ty + dy[i];
                    if(nx < 100 && nx >= 0 && ny < 100 && ny >= 0 && !visited[ny][nx]){
                      if(!visited[ny][nx]){
                        if(!poison[ny][nx]){
                            cost_to_no_poison[i] = nowcost;
                            flag = true;
                            break;
                        }
                        q.push({{nx,ny},nowcost + 1});
                        visited[ny][nx] = true;
                      }
                        
                    }
                }
            }
        }
        ll ans = 0;
        rep(i, n + 1){
            cout << cost_to_no_poison[i] << endl;
        }
        /**/
        rep(i, n){
             //ll cost1 = max(0LL,cost_to_no_poison[i] - 1) + cost_to_no_poison[i + 1];
             ll cost1 = cost_to_no_poison[i] + cost_to_no_poison[i + 1] + 1;
             if(cost_to_no_poison[i] == 0 && cost_to_no_poison[i+1] == 0)cost1 = 0;
             
             ll cost2 = abs(y[i] - y[i+1]) + abs(x[i] - x[i + 1]);
             ans += min(cost1,cost2);
        }
        cout << ans << endl;
    }
    return 0;
}
