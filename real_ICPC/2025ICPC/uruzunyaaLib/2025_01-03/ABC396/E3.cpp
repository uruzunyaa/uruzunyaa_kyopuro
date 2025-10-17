#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL


//重み付きUF
struct XorUnionFind {
	ll n;
	vl par, siz, xr;
	vvl one;
	XorUnionFind(ll N) : par(N,-1) , siz(N,1) , xr(N,0) ,one(30,vl(N,0)){n=N;}
	// 根を求める
	ll root(ll x) {
		if (par[x] == -1) return x;
		ll tmp = root(par[x]);
		xr[x] ^= xr[par[x]];
		par[x] = tmp;
		return par[x];
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(ll x, ll y) {
		return root(x) == root(y);
	}
	//x との xor が w になるように y を併合。
	bool unite(ll x, ll y, ll w) {
		ll rx = root(x),ry = root(y);
		w ^= xr[x] ^ xr[y];
		if (rx == ry && w!=0)return false;
		else if(rx == ry)return true;
		if (siz[rx] < siz[ry]) swap(rx, ry);
		rep(i,30){
			if(w&(1LL<<i))one[i][rx]+=siz[ry]-one[i][ry];
			else one[i][rx]+=one[i][ry];
			one[i][ry]=0;
		}
		par[ry] = rx;
		siz[rx] += siz[ry];
		siz[ry] = 0;
		xr[ry] = w;
		return true;
	}
	ll get(ll x){
		ll rx = root(x);
		ll ans=xr[x];
		rep(i,30)if(siz[rx]/2<one[i][rx])ans^=(1LL<<i);
		return ans;
	}
	// x を含むグループのサイズ
	ll size(ll x) {
		return siz[root(x)];
	}
};


//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	XorUnionFind uf(n);
	rep(i,m){
		ll x,y,z;
		cin>>x>>y>>z;
		x--,y--;
		if(!uf.unite(x,y,z)){
			cout<<-1<<endl;
			return 0;
		}
	}
	rep(i,n)cout<<uf.get(i)<<" ";
	cout<<endl;
	return 0;
}
