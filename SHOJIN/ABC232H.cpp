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
	ll h,w,a,b;
	cin>>h>>w>>a>>b;
	bool swaps=false;
	vector<pair<ll,ll>> ans;
	if(h==a||b==w){
		if(h!=a){
			swap(h,w);
			swap(a,b);
			swaps=true;
		}

		loop(i,1,h-2){
			if(i%2==1){
				loop(j,1,w)ans.push_back({i,j});
			}else{
				rloop(j,w,1)ans.push_back({i,j});
			}
		}

		if(h%2==0){
			loop(j,1,b-1)ans.push_back({h-1,j}),ans.push_back({h,j});
			loop(j,b,w)ans.push_back({h-1,j});
			rloop(j,w,b)ans.push_back({h,j});
		}else{
			rloop(j,w,b+1)ans.push_back({h-1,j}),ans.push_back({h,j});
			rloop(j,b,1)ans.push_back({h-1,j});
			loop(j,1,b)ans.push_back({h,j});
		}

		if(swaps){
			rep(i,ans.size())swap(ans[i].first,ans[i].second);
		}
		rep(i,ans.size()){
			cout<<ans[i].first<<" "<<ans[i].second<<endl;
		}
		return 0;
	}

	if(a==1){
		swap(h,w);
		swap(a,b);
		swaps=true;
	}
	
	
	loop(i,1,(a-2)/2){
		loop(j,1,w)ans.push_back({i*2-1,j});
		rloop(j,w,1)ans.push_back({i*2,j});
	}
	if(a%2==0){
		loop(j,1,b)ans.push_back({a-1,j});
		loop(j,b+1,w)ans.push_back({a-1,j}),ans.push_back({a,j});
	}else{
		loop(j,1,b)ans.push_back({a-2,j}),ans.push_back({a-1,j});
		loop(j,b+1,w)ans.push_back({a-2,j});
		rloop(j,w,b+1)ans.push_back({a-1,j});
		loop(j,b+1,w)ans.push_back({a,j});
	}
	loop(i,1,(h-a-1)/2){
		rloop(j,w,2)ans.push_back({a+i*2-1,j});
		loop(j,2,w)ans.push_back({a+i*2,j});
	}
	if((h-a)%2==0){
		rloop(j,w,2)ans.push_back({h-1,j}),ans.push_back({h,j});
	}else{
		rloop(j,w,2)ans.push_back({h,j});
	}
	rloop(i,h,a+1)ans.push_back({i,1});
	loop(j,1,b)ans.push_back({a,j});

	if(swaps){
		rep(i,ans.size())swap(ans[i].first,ans[i].second);
	}
	rep(i,ans.size()){
		cout<<ans[i].first<<" "<<ans[i].second<<endl;
	}
	return 0;
}
