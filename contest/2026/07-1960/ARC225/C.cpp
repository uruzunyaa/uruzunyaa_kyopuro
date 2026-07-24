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
	int comp;
	vector<int> par, siz;
	UnionFind(int n) : par(n, -1) , siz(n, 1) ,comp(n){ }
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
		comp--;
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

void solve(){
	ll n,m,k;
	cin>>n>>m>>k;
	UnionFind uf0(n),uf1(n);
	vvl g0,g1;
	rep(i,m){
		ll a,b,c;
		cin>>a>>b>>c;
		a--,b--;
		if(c==0){
			if(uf0.issame(a,b))continue;
			uf0.unite(a,b);
			g0.push_back({a,b,i+1});
		}else{
			if(uf1.issame(a,b))continue;
			uf1.unite(a,b);
			g1.push_back({a,b,i+1});
		}
	}
	if(k<n-1-g0.size()||g1.size()<k){
		cout<<-1<<endl;
		return;
	}

	set<ll>ans;
	UnionFind uffin(n);
	for(vl tmp:g1){
		ll a=tmp[0];
		ll b=tmp[1];
		ll ind=tmp[2];
		if(uf0.issame(a,b))continue;
		ans.insert(ind);
		uf0.unite(a,b);
		uffin.unite(a,b);
	}
	
	for(vl tmp:g1){
		ll a=tmp[0];
		ll b=tmp[1];
		ll ind=tmp[2];
		if(ans.size()==k)break;
		ans.insert(ind);
		uffin.unite(a,b);
	}

	for(vl tmp:g0){
		ll a=tmp[0];
		ll b=tmp[1];
		ll ind=tmp[2];
		if(uffin.issame(a,b))continue;
		ans.insert(ind);
		uffin.unite(a,b);
	}

	for(auto val:ans){
		cout<<val<<" ";
	}
	cout<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
