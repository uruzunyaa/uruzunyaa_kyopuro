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
	ll comp;
	vector<int> par, siz;
	UnionFind(int n) : par(n, -1) , siz(n, 1),comp(0LL) { }
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
		comp++;
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};
int main(){
	ll h,w;
	cin>>h>>w;
	vvl a(h,vl(w));
	rep(i,h)rep(j,w)cin>>a[i][j];

	vl lans,rans;
	UnionFind luf(h*w);
	rep(i,h-1){
		if(a[i][0]==a[i+1][0])luf.unite(w*i,w*i+w);
	}
	lans.push_back(h-luf.comp);
	loop(j,1,w-1){
		rep(i,h){
			if(a[i][j-1]==a[i][j])luf.unite(w*i+j,w*i+j-1);
		}
		rep(i,h-1){
			if(a[i][j]==a[i+1][j])luf.unite(w*i+j,w*i+j+w);
		}
		lans.push_back((j+1)*h-luf.comp);
	}
	UnionFind ruf(h*w);
	rep(i,h-1){
		if(a[i][w-1]==a[i+1][w-1])ruf.unite(w*i+w-1,w*i+w+w-1);
	}
	rans.push_back(h-ruf.comp);
	rloop(j,w-2,0){
		rep(i,h){
			if(a[i][j+1]==a[i][j])ruf.unite(w*i+j,w*i+j+1);
		}
		rep(i,h-1){
			if(a[i][j]==a[i+1][j])ruf.unite(w*i+j,w*i+j+w);
		}
		rans.push_back((w-j)*h-ruf.comp);
	}
	reverse(rans.begin(),rans.end());
	ll ans=inf;
	rep(i,w-1)ans=min(ans,rans[i+1]+lans[i]);
	cout<<ans<<endl;
	return 0;
}
