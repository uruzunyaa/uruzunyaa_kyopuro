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
#define inf 100000000000000000LL
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

void dfs(ll node,vl & tmp,vvl &ans,ll k){
	if(tmp.size()==k){
		ans.push_back(tmp);
		return;
	}
	rep(i,node){
		tmp.push_back(i);
		dfs(i,tmp,ans,k);
		tmp.pop_back();
	}
	return;
}


//メイン
int main(){
	ll n,m,k;
	cin>>n>>m>>k;
	vvl dist(n,vl(n,inf));
	
	vector<vector<pair<ll,ll>>> g(n);

	rep(i,m){
		ll u,v,w;
		cin>>u>>v>>w;
		u--,v--;
		dist[u][v]=w;
		dist[v][u]=w;
		g[u].push_back({w,v});
		g[v].push_back({w,u});
	}
	rep(i,n)sort(g[i].begin(),g[i].end());
	
	vvl list;
	ll ans=inf;
	vl tmp;
	dfs(n,tmp,list,k-1);
	rep(i,list.size()){
		set<ll> st;
		rep(j,k-1)st.insert(list[i][j]);
		vvl costs;
		rep(j,k-1)rep(e,j){
			costs.push_back({dist[list[i][j]][list[i][e]],j,e});
		}
		ll tmpcost=0;
		sort(costs.begin(),costs.end());
		UnionFind uf(k-1);
		rep(j,costs.size()){
			if(uf.issame(costs[j][1],costs[j][2]))continue;
			uf.unite(costs[j][1],costs[j][2]);
			tmpcost+=costs[j][0];
		}
		if(uf.size(0)!=k-1)continue;
		ll mins=inf;
		rep(j,k-1){
			for(auto val:g[list[i][j]]){
				if(st.count(val.second))continue;
				mins=min(mins,val.first);
				break;
			}
		}
		ans=min(ans,tmpcost+mins);
	}
	cout<<ans<<endl;
	return 0;
}
