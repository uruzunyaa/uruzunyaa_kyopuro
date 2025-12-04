#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//グラフgを受け取り、頂点0から頂点n-1への流量Xを達成する最小コストを求める
//vectorの順序は{行き先,流量,費用}
//不可能な場合-1
ll min_cost_flow(vvvl &g, ll x){
    ll n = (ll)g.size();
    struct Edge {
        ll to, rev, cap, cost;
    };
    vector<vector<Edge>> G(n);

    auto add_edge = [&](ll fr, ll to, ll cap, ll cost){
        Edge f = {to, (ll)G[to].size(), cap, cost};
        Edge r = {fr, (ll)G[fr].size(), 0, -cost};
        G[fr].push_back(f);
        G[to].push_back(r);
    };

    // 入力 g から残余グラフを構築
    for (ll u = 0; u < n; u++) {
        for (auto &e : g[u]) {
            ll v = e[0], cap = e[1], cost = e[2];
            if (cap <= 0) continue;
            add_edge(u, v, cap, cost);
        }
    }

    ll s = 0, t = n - 1;
    ll res = 0;
    const ll INFLL = inf;

    vector<ll> h(n), dist(n), prevv(n), preve(n);

    // 初期ポテンシャルを Bellman-Ford で計算（負辺対応）
    fill(h.begin(), h.end(), INFLL);
    h[s] = 0;
    bool upd = true;
    while (upd) {
        upd = false;
        for (ll v = 0; v < n; v++) {
            if (h[v] == INFLL) continue;
            for (auto &e : G[v]) {
                if (e.cap > 0 && h[e.to] > h[v] + e.cost) {
                    h[e.to] = h[v] + e.cost;
                    upd = true;
                }
            }
        }
    }
    // 到達不能な頂点は 0 にしておく（以後の差分だけ使うのでOK）
    for (ll i = 0; i < n; i++) if (h[i] == INFLL) h[i] = 0;

    while (x > 0) {
        // ポテンシャル付きダイクストラで s->t の最短路を探す
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
        fill(dist.begin(), dist.end(), INFLL);
        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, v] = pq.top(); pq.pop();
            if (dist[v] < d) continue;
            for (ll i = 0; i < (ll)G[v].size(); i++) {
                Edge &e = G[v][i];
                if (e.cap <= 0) continue;
                ll nd = d + e.cost + h[v] - h[e.to];
                if (dist[e.to] > nd) {
                    dist[e.to] = nd;
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    pq.push({nd, e.to});
                }
            }
        }

        if (dist[t] == INFLL) {
            // これ以上流せない（流量 x を満たせない）
            return -1;
        }

        // ポテンシャル更新
        for (ll v = 0; v < n; v++) {
            if (dist[v] < INFLL) h[v] += dist[v];
        }

        // この経路に流せる最大量 d を決定
        ll d = x;
        for (ll v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        x -= d;
        res += d * h[t];

        // 残余グラフの更新
        for (ll v = t; v != s; v = prevv[v]) {
            Edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }

    return res;
}


int main(){
	
	return 0;
}
