#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
// Union-Find
struct UnionFind {
	vector<int> par, siz,cnt;
	UnionFind(int n) : par(n, -1) , siz(n, 1),cnt(n,0) { }
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
		cnt[x] += cnt[y];
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
	int cnts(int x) {
		return cnt[root(x)];
	}
	void cntpp(int x){
		cnt[root(x)]++;
		return;
	}
};
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

int main(){
	ll n,m;
	cin>>n>>m;
	UnionFind uf(n);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		uf.unite(a,b);
		uf.cntpp(a);
	}
	set<ll> st;
	rep(i,n){
		if(uf.size(i)!=uf.cnts(i)){
			cout<<0<<endl;
			return 0;
		}
		st.insert(uf.root(i));
	}
	cout<<power_mod(2,st.size())<<endl;
	return 0;
}
