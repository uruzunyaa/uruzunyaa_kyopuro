#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
const ll MOD = 998244353;
const ll INF = 1LL << 60;

ll dy[] = {0, 1, 0, -1};
ll dx[] = {1, 0, -1, 0};

int main(){
    ll n, m;
    cin >> n >> m;
    vector<string> s(n);
    pair<ll, ll> start, end;
    vector<vector<vector<ll>>> dist(n, (vector<vector<ll>>(m, vector<ll>(4, INF))));
    rep(i, n){
        cin >> s[i];
        rep(j, m){
            if(s[i][j] == 'S'){
                start.first = i;
                start.second = j;
            }
            else if(s[i][j] == 'E'){
                end.first = i;
                end.second = j;
            }
        }
    }
    ll ans = -1;
    queue<pair<pair<ll, ll>, pair<ll, ll>>> q;
    q.push({{start.first, start.second}, {0, -1}});
    dist[start.first][start.second][0] = 0;
    dist[start.first][start.second][1] = 0;
    dist[start.first][start.second][2] = 0;
    dist[start.first][start.second][3] = 0;
    while(!q.empty()){
        auto [p1, p2] = q.front();
        auto [y, x] = p1;
        // dire 0 = 上 1 = 右 2 = 下 3 = 左
        auto [cost, dire] = p2;
        q.pop();
        if(y == end.first && x == end.second){
            ans = cost;
            break;
        }
        rep(i, 4){
            // 右方向に曲がる場合
            if(dire == i)continue;
            ll ny = y + dy[i];
            ll nx = x + dx[i];
            if(ny >= n || ny < 0 || nx >= m || nx < 0)continue;
            if(s[ny][nx] == '#')continue;
            // dire 0上 1右 2下 3左
            // dxdy 0右 1下 2左 3上
            ll next = (i + 1) % 4;
            if(dist[ny][nx][next] < cost + 1)continue;
            q.push({{ny, nx},{cost + 1, next}});
            dist[ny][nx][next] = min(dist[ny][nx][next], cost + 1);
        }
    }
    cout << ans << '\n';
}