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

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	n%=mod;
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return ans;
}

//受け取った2次元文字の外側に、文字pをコーティングする。
vector<string> pad(vector<string> &s,char p){
	ll h=s.size();
	ll w=s[0].size();
	vector<string> res(h+2,string(w+2,p));
	rep(i,h)rep(j,w)res[i+1][j+1]=s[i][j];
	return res;
}

// Union-Find
struct UnionFind {
	vector<int> par, siz;
	UnionFind(int n) : par(n, -1) , siz(n, 1) { }
	// 根を求める
	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(int x, int y) {
		return root(x) == root(y);
	}
	// x を含むグループと y を含むグループとを併合する
	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false; 
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};


//グラフgの頂点startからの最短経路を全ての頂点に対して求める。
//到達不可はinf
//pairの順序は{行き先,コスト}
vl dijkstra(vector<vector<pair<ll,ll>>> &g,ll start){
	priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> dj;
	vl cost(g.size(),inf);
	cost[start]=0;
	dj.push({0,start});
	while(!dj.empty()){
		ll nowcost=dj.top().first;
		ll tmp=dj.top().second;
		dj.pop();
		if(cost[tmp]<nowcost)continue;
		rep(i,g[tmp].size()){
			ll nxnode=g[tmp][i].first;
			ll nxcost=g[tmp][i].second;
			if(cost[nxnode]>nowcost+nxcost){
				cost[nxnode]=nowcost+nxcost;
				dj.push({cost[nxnode],nxnode});
			}
		}
	}
	return cost;
}


//メイン
//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro

ll getind(ll takasa,ll node,ll n){
	return takasa*n+node;
}

int main(){
	ll n,m,k,souti;
	cin>>n>>m>>k>>souti;
	ll s,t;
	cin>>s>>t;
	vl p(n),q(n);
	rep(i,n)cin>>p[i]>>q[i];
	vl a(m),b(m),l(m),r(m),c(m),h(m),d(m);

	rep(i,m){
		cin>>a[i]>>b[i]>>l[i]>>r[i]>>c[i]>>h[i]>>d[i];
		a[i]--,b[i]--;
	}
	ll ans=inf;

	rep(v,k+1)rep(u,v+1){
		//高さ+拠点番号
		vector<vector<pair<ll,ll>>> g(n*(k+1));
		rep(x,k+1){
			if(x<u||v<x)continue;
			rep(j,m){
				if(l[j]>x||x>r[j])continue;
				ll cost=c[j]+d[j]*abs(x-h[j]);
				g[getind(x,a[j],n)].push_back({getind(x,b[j],n),cost});

			}
		}
		rep(x,k){
			if(x<u||v<x)continue;
			if(x+1<u||v<x+1)continue;
			rep(i,n){
				g[getind(x,i,n)].push_back({getind(x+1,i,n),p[i]});
				g[getind(x+1,i,n)].push_back({getind(x,i,n),q[i]});
			}
		}
		ll tmp=dijkstra(g,getind(s,0,n))[getind(t,n-1,n)];
		tmp+=souti*(v-u);
		ans=min(ans,tmp);
	}
	if(ans==inf){
		cout<<"NA"<<endl;
	}else{
		cout<<ans<<endl;
	}

	return 0;
}
