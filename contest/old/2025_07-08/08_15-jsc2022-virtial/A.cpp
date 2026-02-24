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
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

//nCr % mod を O(max(n)) で求める(power_mod前提条件)
vl fact={1};
vl factinv={1};
ll ncrmd(ll n,ll r){
	while(fact.size()<=n){
		ll i=fact.size();
		fact.push_back((fact[i-1]*i)%mod);
		factinv.push_back(power_mod(fact[i],mod-2));
	}
	ll ans=fact[n];
	ans*=factinv[r];
	ans%=mod;
	ans*=factinv[n-r];
	ans%=mod;
	return ans;
}

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

// Union-Find
struct UnionFind {
	vector<int> par, siz ,mx;
	UnionFind(int n) : par(n, -1) , siz(n, 1) ,mx(n,0){ 
		rep(i,n)mx[i]=i;
	}
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
		mx[x] = max(mx[x],mx[y]);
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};



//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vvl g(n);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		g[max(a,b)].push_back(min(a,b));
	}
	UnionFind uf(n);

	//{サイズ,通り}
	vector<pair<ll,ll>> dp(n,{0,1});

	rep(i,n){
		rep(j,g[i].size()){
			ll tmp=uf.mx[uf.root(g[i][j])];
			if(uf.issame(tmp,i))continue;

			dp[i].first+=dp[tmp].first;
			dp[i].second*=dp[tmp].second;
			dp[i].second%=mod;
			dp[i].second*=ncrmd(dp[i].first,dp[tmp].first);
			dp[i].second%=mod;
			
			//dp[tmp]={0,1};
			uf.unite(tmp,i);
			//cout<<dp[i].first<<" "<<dp[i].second<<endl;
		}
		dp[i].first++;
		//cout<<dp[i].first<<" "<<dp[i].second<<endl;
	}
	cout<<dp[n-1].second<<endl;
	
	return 0;
}
