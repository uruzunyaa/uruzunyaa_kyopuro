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


//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro

void dfs123(ll node,ll mae,ll cnt,UnionFind & uf,vvl & g){
	ll n=g.size();
	if(uf.size(node)!=1)return;
	uf.unite(node,n+cnt);
	for(auto val:g[node]){
		if(val==mae)continue;
		dfs123(val,node,(cnt+1)%3,uf,g);
	}
}

void dfs34(ll node,ll mae,ll cnt,UnionFind & uf,vvl & g){
	ll n=g.size();
	if(uf.size(node)!=1)return;
	ll ind=min(cnt,1LL);
	ind+=n+3;
	uf.unite(node,ind);
	for(auto val:g[node]){
		if(val==mae)continue;
		dfs34(val,node,(cnt+1)%3,uf,g);
	}
}

//メイン
int main(){
	ll n,m,q;
	cin>>n>>m>>q;
	string s;
	cin>>s;
	vvl g(n);
	rep(i,m){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vl ziyu;
	rep(i,n){
		if(g[i].size()>=3)ziyu.push_back(i);
	}

	UnionFind uf(n+5);
	//n:0番頂点
	//n+1:1番頂点
	//n+2:2番頂点
	//n+3:自由頂点
	//n+4:不自由頂点集合

	bool type3=false;

	if(ziyu.size()==0){
		//サイクルかパス
		if(m==n){
			//サイクル
			if(n%3!=0){
				//自由サイクルなので全て自由にして同様に。
				rep(i,n)uf.unite(n+3,i);
			}else{
				//不自由サイクルなのでパスグラフと同じに。
				dfs123(0,g[0][0],0,uf,g);
				type3=true;
			}
		}else{
			//パスグラフ
			ll happa;
			rep(i,n)if(g[i].size()==1)happa=i;
			dfs123(happa,-1,0,uf,g);
			type3=true;
		}
	}else{
		//n+3:自由頂点
		//n+4:不自由頂点集合
		dfs34(ziyu[0],-1,0,uf,g);
		for(auto val:ziyu){
			uf.unite(val,n+3);
			for(auto tonari:g[val]){
				uf.unite(tonari,n+4);
			}
		}
		if(uf.issame(n+3,n+4)){
			//自由サイクルなので全て自由にして同様に。
			rep(i,n)uf.unite(n+3,i);
		}
	}

	uf.unite(n,n+3);
	uf.unite(n+1,n+4);

	vl now(3,0);
	rep(i,n){
		if(s[i]=='1'){
			if(uf.issame(i,n)){
				now[0]^=1;
			}else if(uf.issame(i,n+1)){
				now[1]^=1;
			}else{
				now[2]^=1;
			}
		}
	}
	

	while(q--){
		ll x;
		cin>>x;
		x--;
		if(uf.issame(x,n)){
			now[0]^=1;
		}else if(uf.issame(x,n+1)){
			now[1]^=1;
		}else{
			now[2]^=1;
		}

		
		if(type3){
			//自由頂点がなく、3つが一致必須。
			if(now[0]==now[1]&&now[0]==now[2]){
				cout<<"Yes"<<endl;
			}else{
				cout<<"No"<<endl;
			}
		}else{
			//自由頂点でない奴の偶奇が不変量。
			if(now[1]==0){
				cout<<"Yes"<<endl;
			}else{
				cout<<"No"<<endl;
			}
		}
	}
	return 0;
}
