//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
struct Edge {
    long long to;
};
using Graph = vector<vector<Edge>>;

/* LCA(G, root): 木 G に対する根を root として Lowest Common Ancestor を求める構造体
    query(u,v): u と v の LCA を求める。計算量 O(logn)
    前処理: O(nlogn)時間, O(nlogn)空間
*/
struct LCA {
    vector<vector<int>> parent;  // parent[k][u]:= u の 2^k 先の親
    vector<int> dist;            // root からの距離
    LCA(const Graph &G, int root = 0) { init(G, root); }

    // 初期化
    void init(const Graph &G, int root = 0) {
        int V = G.size();
        int K = 1;
        while ((1 << K) < V) K++;
        parent.assign(K, vector<int>(V, -1));
        dist.assign(V, -1);
        dfs(G, root, -1, 0);
        for (int k = 0; k + 1 < K; k++) {
            for (int v = 0; v < V; v++) {
                if (parent[k][v] < 0) {
                    parent[k + 1][v] = -1;
                } else {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
    }

    // 根からの距離と1つ先の頂点を求める
    void dfs(const Graph &G, int v, int p, int d) {
        parent[0][v] = p;
        dist[v] = d;
        for (auto e : G[v]) {
            if (e.to != p) dfs(G, e.to, v, d + 1);
        }
    }

    int query(int u, int v) {
        if (dist[u] < dist[v]) swap(u, v);  // u の方が深いとする
        int K = parent.size();
        // LCA までの距離を同じにする
        for (int k = 0; k < K; k++) {
            if ((dist[u] - dist[v]) >> k & 1) {
                u = parent[k][u];
            }
        }
        // 二分探索で LCA を求める
        if (u == v) return u;
        for (int k = K - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
	int get_dist(int u, int v) { return dist[u] + dist[v] - 2 * dist[query(u, v)]; }
	bool is_on_path(int u, int v, int a) { return get_dist(u, a) + get_dist(a, v) == get_dist(u, v); }
};

Graph sg;
ll ans=0;
vl cnt;
pair<ll,bool> tdfs(ll mae,ll node,Graph & g){
	bool one=false;
	if(node==1)one=true;
	ll siz=1;
	rep(i,g[node].size()){
		if(g[node][i].to==mae)continue;
		sg[node].push_back({g[node][i].to});
		auto [tsiz,tone]=tdfs(node,g[node][i].to,g);
		if(node!=0||true!=tone)siz+=tsiz;
		if(tone)one=true;

		if(node==0){
			ans-=tsiz*(tsiz+1)/2;
		}
	}
	cnt[node]=siz;
	return {siz,one};
}

//メイン
int main(){
	ll n;
	cin>>n;
	ans+=n*(n+1)/2;
	Graph tg(n);
	sg=Graph(n);
	cnt = vl(n);
	rep(i,n-1){
		ll u,v;
		cin>>u>>v;
		tg[u].push_back({v});
		tg[v].push_back({u});
	}
	tdfs(-1,0,tg);

	LCA lca(sg);
	ll left=0,right=0;

	loop(i,1,n-1){
		if(!lca.is_on_path(left,right,i)){
			if(lca.query(left,i)==left){
				left=i;
			}else if(lca.query(right,i)==right){
				right=i;
			}else{
				break;
			}
		}
		if(!lca.is_on_path(left,right,0))break;
		ans+=cnt[left]*cnt[right];
	}
	cout<<ans<<endl;
	return 0;
}