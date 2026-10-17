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


//左側のノード数,右側のノード数,マッチング出来る物のリストを受け取り
//最大2部マッチングを返す
//計算量:O(VE)
ll bipartite_matching(ll mxa,ll mxb,vector<pair<ll,ll>> ok){
	// 隣接リスト (左側 -> 右側)
    vvl g(mxa);
    for(auto &e : ok){
        ll a = e.first;
        ll b = e.second;
        g[a].push_back(b);
    }

    // 右側の各頂点がどの左頂点にマッチしているか (-1:未マッチ)
    vl matchR(mxb, -1);

    // 増加路探索のDFS,既にマッチ済みを付け替えれるなら付け替えながら
    auto dfs = [&](auto&& self, ll v, vl &used) -> bool {
        for(ll u : g[v]){
            if(used[u]) continue;
            used[u] = 1;
            if(matchR[u] == -1 || self(self, matchR[u], used)){
                matchR[u] = v;
                return true;
            }
        }
        return false;
    };

    ll ret = 0;
    for(ll v = 0; v < mxa; v++){
        vl used(mxb, 0);
        if(dfs(dfs, v, used)) ret++;
    }
    return ret;
}




void solve(){
	ll n;
	cin>>n;
	vl a(n),b(n);
	ll oddcnta=0,oddcntb=0;
	rep(i,n){
		cin>>a[i];
		if(abs(a[i])%2!=0)oddcnta++;
	}
	rep(i,n){
		cin>>b[i];
		if(abs(b[i])%2!=0)oddcntb++;
	}

	ll mnsums=inf;

	if(oddcnta==oddcntb){
		//奇数同士
		ll mn=0,mx=2000000001;
		while(mn!=mx){
			ll midd=mn+mx;
			midd/=2;
			ll mid=midd*2;
			vector<pair<ll,ll>> ok;
			rep(i,n)rep(j,n){
				ll sa=abs(abs(a[i])-abs(b[j]));
				if(sa<=mid&&abs(a[i])%2==abs(b[j])%2){
					ok.push_back({i,j});
				}
			}
			if(bipartite_matching(n,n,ok)==n)mx=midd;
			else mn=midd+1;
		}
		if(mn!=2000000001)mnsums=min(mnsums,mn*2);
	}

	if(oddcnta==n-oddcntb){
		//奇数と偶数をマッチング
		ll mn=0,mx=2000000001;
		while(mn!=mx){
			ll midd=mn+mx;
			midd/=2;
			ll mid=midd*2+1;
			vector<pair<ll,ll>> ok;
			rep(i,n)rep(j,n){
				ll sa=abs(abs(a[i])-abs(b[j]));
				if(sa<=mid&&abs(a[i])%2!=abs(b[j])%2){
					ok.push_back({i,j});
				}
			}
			if(bipartite_matching(n,n,ok)==n)mx=midd;
			else mn=midd+1;
		}
		if(mn!=2000000001)mnsums=min(mn*2+1,mnsums);
	}
	if(mnsums==inf){
		cout<<-1<<'\n';
		return;
	}

	ll ans=inf;
	loop(pluscnt,max(mnsums-4,0LL),mnsums+n*2){
		vvvl g(n*2+2);
		//vectorの順序は{行き先,流量,費用}
		loop(j,1,n){
			g[0].push_back({j,1,0});
			g[n+j].push_back({n*2+1,1,0});
		}
		rep(j,n)rep(k,n){
			ll sa=abs(a[j]-b[k]);
			if(sa%2==pluscnt%2){
				if(b[k]-a[j]==pluscnt){
					g[j+1].push_back({n+k+1,1,0});
				}else if(abs(a[j]+b[k])<=pluscnt){
					g[j+1].push_back({n+k+1,1,1});
				}else if(abs(abs(a[j])-abs(b[k]))<=pluscnt){
					g[j+1].push_back({n+k+1,1,2});
				}
			}
		}
		ll tmpss=min_cost_flow(g,n);
		if(tmpss!=-1)ans=min(ans,tmpss+pluscnt);
	}

	cout<<ans<<'\n';
	return;
}

//メイン
int main(){
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
