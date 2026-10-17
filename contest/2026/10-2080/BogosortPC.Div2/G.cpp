//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
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


//メイン
int main(){
	ll n,k,l,r;
	cin>>n>>k>>l>>r;
	if(3*l>n){
		cout<<-1<<endl;
		return 0;
	}

	vl t(n);
	rep(i,n)cin>>t[i];

	ll x,y,z;
	cin>>x>>y>>z;
	vl d(x+y+z),f(x+y+z);
	rep(i,x+y+z)cin>>d[i]>>f[i];
	ll tuika=100000000000000;
	ll mpena=1000000000;

	vvvl g(x+y+z+n+6);
	//{行き先,流量,費用}
	g[0].push_back({1,3*l,0});
	g[1].push_back({2,l,0});
	g[1].push_back({3,l,0});
	g[1].push_back({4,l,0});
	g[0].push_back({2,r-l,tuika});
	g[0].push_back({3,r-l,tuika});
	g[0].push_back({4,r-l,tuika});
	
	rep(i,x){
		g[2].push_back({i+5,1,mpena-f[i]});
	}
	loop(i,x,x+y-1){
		g[3].push_back({i+5,1,mpena-f[i]});
	}
	loop(i,x+y,x+y+z-1){
		g[4].push_back({i+5,1,mpena-f[i]});
	}

	rep(i,x+y+z)rep(j,n){
		if(abs(d[i]-t[j])>k)continue;
		g[i+5].push_back({x+y+z+5+j,1,0});
	}
	rep(i,n){
		g[i+5+x+y+z].push_back({n+5+x+y+z,1,0});
	}

	ll mincos=min_cost_flow(g,n);
	if(mincos==-1){
		cout<<-1<<endl;
		return 0;
	}

	if(mincos==-1){
		cout<<-1<<endl;
		return 0;
	}
	mincos-=(n-3*l)*tuika;
	if(mincos>=tuika){
		cout<<-1<<endl;
		return 0;
	}

	mincos-=mpena*n;
	cout<<-mincos<<endl;
	return 0;
}
