#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL

//グラフgの頂点startからの最短経路を全ての頂点に対して求める。
//到達不可負はinf,経路上に負閉路があれば-inf
//pairの順序は{行き先,コスト}
vl bellman_ford(vector<vector<pair<ll,ll>>> &g, ll start){
    ll n = g.size();
    vl dist(n, inf);
    dist[start] = 0;

    // 1. 通常の Bellman-Ford: n-1 回緩和
    rep(iter, n-1){
        bool updated = false;
        rep(u, n){
            if (dist[u] == inf || dist[u] == -inf) continue;
            for (auto &e : g[u]){
                ll v = e.first;
                ll c = e.second;
                if (dist[v] > dist[u] + c){
                    dist[v] = dist[u] + c;
                    updated = true;
                }
            }
        }
        if (!updated) break; // もう更新されないなら終了
    }

    // 2. 負閉路の検出＆-inf 伝播
    // 追加で n 回まわして、負閉路から到達可能な頂点を -inf にする
    rep(iter, n){
        rep(u, n){
            if (dist[u] == inf) continue;
            for (auto &e : g[u]){
                ll v = e.first;
                ll c = e.second;

                // すでに -inf なら先にも伝播
                if (dist[u] == -inf){
                    if (dist[v] != -inf){
                        dist[v] = -inf;
                    }
                    continue;
                }

                // まだ短くできるなら、u->v は負閉路の影響を受けている
                if (dist[v] > dist[u] + c){
                    dist[v] = -inf;
                }
            }
        }
    }

    return dist;
}

int main(){
	return 0;
}
