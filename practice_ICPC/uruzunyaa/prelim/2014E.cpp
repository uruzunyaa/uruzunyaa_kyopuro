//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 1e9
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
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
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
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

vl dist;
vector<vector<pair<ll,ll>>> g;

void dfs(ll before,ll node){
	rep(i,g[node].size()){
		if(g[node][i].first==before)continue;
		//次が葉じゃなければ遷移
		if(g[g[node][i].first].size()==1)continue;
		dist[g[node][i].first]=dist[node]+g[node][i].second;
		dfs(node,g[node][i].first);
	}
}

ll solve(){
	ll n;
	cin>>n;
	if(n==0){return 1;}

	dist=vl(n,0);
	g=vector<vector<pair<ll,ll>>>(n);
	
	vl p(n);
	vl d(n);

	ll ans=0;

	loop(i,1,n-1)cin>>p[i],p[i]--;
	loop(i,1,n-1)cin>>d[i];

	loop(i,1,n-1){
		g[i].push_back({p[i],d[i]});
		g[p[i]].push_back({i,d[i]});
		ans+=d[i];
	}

	//葉以外同士辺を全て2回足す
	rep(i,n){
		if(g[i].size()==1)continue;
		rep(j,g[i].size()){
			if(g[g[i][j].first].size()==1)continue;
			ans+=g[i][j].second;
		}
	}

	ll mxi;
	rep(i,n){
		if(g[i].size()==1)continue;
		dfs(-1,i);
		mxi=i;
		break;
	}

	rep(i,n){
		if(g[i].size()==1)continue;
		if(dist[i]>dist[mxi])mxi=i;
	}
	dist=vl(n);
	dfs(-1,mxi);
	rep(i,n){
		if(g[i].size()==1)continue;
		if(dist[i]>dist[mxi])mxi=i;
	}

	ans-=dist[mxi];
	cout<<ans<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
