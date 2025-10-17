#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for (ll i = 0; i < n; ++i)

int dx[] = {1,0,0,-1};
int dy[] = {0,1,-1,0};
int main(){
    ll n,m;
    cin >> n >> m;
    vector<string> x(n);
    rep(i, n){
        cin >> x[i];
    }
    string yokohama = "YOKOHAMA";
    queue<pair<pair<ll,ll>,ll>> q;
    rep(i, n){
        rep(j, m){
            if(x[i][j] == 'Y'){
                q.push({{j,i},0});
            }
        }
    }
    ll ans = 0;
    while(!q.empty()){
        ll nowx = q.front().first.first;
        ll nowy = q.front().first.second;
        ll now = q.front().second;
        q.pop();
        if(now == yokohama.length() - 1){
            ans++;
            continue;
        }
        rep(i, 4){
            ll nx = nowx + dx[i];
            ll ny = nowy + dy[i];
            if(nx < m && nx >= 0 && ny < n && ny >= 0){
                if(x[ny][nx] == yokohama[now + 1]){
                    q.push({{nx,ny},now + 1});
                }
            }
        }
    }
    cout << ans << endl;
}