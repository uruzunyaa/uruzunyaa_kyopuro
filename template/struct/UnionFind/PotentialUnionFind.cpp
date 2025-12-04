#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

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

int main(){

	return 0;
}
