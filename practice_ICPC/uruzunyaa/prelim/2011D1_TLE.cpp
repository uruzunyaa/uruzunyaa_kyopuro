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

ll s;
vvl u;
map<vl,pair<ll,ll>> dp;
pair<ll,ll> dfs(vl &a){
	if(dp.count(a))return dp[a];

	ll sum=0;
	loop(i,a[0],a[2])loop(j,a[1],a[3]){
		sum+=u[i][j];
	}
	if(sum<s){
		pair<ll,ll> ans={-inf,0};
		dp[a]=ans;
		return ans;
	}
	pair<ll,ll> ans={1,sum-s};
	
	//iの下に横線で切る
	loop(i,a[0],a[2]-1){
		vl first={a[0],a[1],i,a[3]};
		vl second={i+1,a[1],a[2],a[3]};
		pair<ll,ll> tmp=dfs(first);
		pair<ll,ll> tmp2=dfs(second);
		ans=max(ans,{tmp.first+tmp2.first,min(tmp.second,tmp2.second)});
	}

	//iの右に縦線で切る
	loop(i,a[1],a[3]-1){
		vl first={a[0],a[1],a[2],i};
		vl second={a[0],i+1,a[2],a[3]};
		pair<ll,ll> tmp=dfs(first);
		pair<ll,ll> tmp2=dfs(second);
		ans=max(ans,{tmp.first+tmp2.first,min(tmp.second,tmp2.second)});
	}

	dp[a]=ans;
	return ans;
}

ll solve(){
	ll h,w;
	cin>>h>>w>>s;
	if(h==0){return 1;}
	u=vvl(h,vl(w));
	rep(i,h)rep(j,w)cin>>u[i][j];

	ll sum=0;
	rep(i,h)rep(j,w){
		sum+=u[i][j];
	}
	s=sum-s;

	vl tmp={0,0,h-1,w-1};
	pair<ll,ll> ans=dfs(tmp);
	cout<<ans.first<<" "<<ans.second<<"\n";
	
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
