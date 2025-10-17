#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353

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

int main(){
	ll n,d;
	cin>>n>>d;
	d*=d;
	vl x(n),y(n);
	rep(i,n)cin>>x[i]>>y[i];
	UnionFind uf(n);
	rep(i,n)rep(j,i){
		if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=d){
			uf.unite(i,j);
		}
	}
	rep(i,n){
		if(uf.issame(0,i))cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}