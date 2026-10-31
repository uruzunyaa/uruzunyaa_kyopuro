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


//重み付きUF
//頂点同士の差を管理できる
struct PotentialUnionFind {
	ll n;
	vl par, siz, pot;
	PotentialUnionFind(ll N) : par(N,-1) , siz(N,1) , pot(N,0){n=N;}
	// 根を求める
	ll root(ll x) {
		if (par[x] == -1) return x;
		ll tmp = root(par[x]);
		pot[x] += pot[par[x]];
		par[x] = tmp;
		return par[x];
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(ll x, ll y) {
		return root(x) == root(y);
	}
	//x よりいくつ大きい所に y があるか。根が一致しない場合は"0"
	ll potential(ll x,ll y){
		if(root(x) != root(y)) return 0;
		else return pot[y]-pot[x];
	}
	//x より w だけ大きい状態として y を併合。
	bool unite(ll x, ll y, ll w) {
		ll rx = root(x),ry = root(y);
		if (rx == ry) return false;
		w += pot[x]-pot[y];
		if (siz[rx] < siz[ry]) swap(rx, ry),w*=-1;
		par[ry] = rx;
		siz[rx] += siz[ry];
		siz[ry] = 0;
		pot[ry] = w;
		return true;
	}
	// x を含むグループのサイズ
	ll size(ll x) {
		return siz[root(x)];
	}
	//小さい順にUnionFindグラフを調整、O(n log n)
	void regulation(){
		vvl r(n);
		rep(i,n)r[root(i)].push_back(i);
		rep(i,n){
			if(r[i].size()==0)continue;
			ll mn = i;
			rep(j,r[i].size())if(pot[mn]>pot[r[i][j]])mn=r[i][j];
			siz[mn]=siz[i];
			siz[i]=0;
			ll tmp = pot[mn];
			rep(j,r[i].size()){
				pot[r[i][j]]-=tmp;
				par[r[i][j]] = mn;
			}
			par[mn]=-1;
		}
	}
	void debug(){
		rep(i,n)cout<<setw(4)<<left<<par[i]<<" ";
		cout<<endl;
		rep(i,n)cout<<setw(4)<<left<<pot[i]<<" ";
		cout<<endl;
	}
};



//メイン
//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro

void solve(){
	ll n,m;
	cin>>n>>m;
	PotentialUnionFind uf(n);
	string ans="YES";
	rep(i,m){
		ll a,b,c;
		cin>>a>>b>>c;
		a--,b--;
		if(uf.issame(a,b)){
			if(uf.potential(a,b)!=c){
				ans="NO";
			}
		}else{
			uf.unite(a,b,c);
		}
	}
	cout<<ans<<endl;
}

int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
