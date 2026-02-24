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


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//乱数、ファイル入出力
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

struct node{
	ll to,cost;
};
//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl bfd(n+1,0);
	vector<vector<node>> g(n+1);
	rep(i,m){
		ll l,r,s;
		cin>>l>>r>>s;
		l--;
		g[l].push_back({r,s});
		g[r].push_back({l,-s});
	}
	loop(i,1,n)g[i].push_back({i-1,-1});

	bool f;
	//ベルマンフォードの試行回数
	rep(i,n+1){
		f=false;
		//全ての頂点を順番に処理
		rep(j,n+1){
			rep(k,g[j].size()){
				if(bfd[g[j][k].to]>bfd[j]+g[j][k].cost){
					f=true;
					bfd[g[j][k].to]=bfd[j]+g[j][k].cost;
				}
			}
		}
	}
	if(f)cout<<-1<<endl;
	else cout<<-bfd[0]<<endl;
	return 0;
}
