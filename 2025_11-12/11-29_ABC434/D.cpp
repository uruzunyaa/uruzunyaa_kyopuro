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


//メイン
int main(){
	ll siz=2000;
	vvl imos(siz+1,vl(siz+1,0));

	ll n;
	cin>>n;
	ll ans=siz*siz;
	vl u(n),d(n),l(n),r(n);
	rep(i,n){
		cin>>u[i]>>d[i]>>l[i]>>r[i];
		u[i]--,l[i]--;
		imos[u[i]][l[i]]++;
		imos[d[i]][r[i]]++;
		imos[u[i]][r[i]]--;
		imos[d[i]][l[i]]--;
	}
	rep(i,siz)rep(j,siz){
		if(i!=0)imos[i][j]+=imos[i-1][j];
		if(j!=0)imos[i][j]+=imos[i][j-1];
		if(j!=0&&i!=0)imos[i][j]-=imos[i-1][j-1];
	}


	rep(i,siz)rep(j,siz){
		if(imos[i][j]!=0)ans--;
		if(imos[i][j]!=1)imos[i][j]=0;
	}


	vvl check(siz+1,vl(siz+1,0));
	loop(i,1,siz)loop(j,1,siz){
		check[i][j]=check[i-1][j]+check[i][j-1]-check[i-1][j-1]+imos[i-1][j-1];
	}

	rep(i,n){
		ll tmp=ans+(check[d[i]][r[i]]+check[u[i]][l[i]]-check[u[i]][r[i]]-check[d[i]][l[i]]);
		cout<<tmp<<endl;
	}
	return 0;
}
