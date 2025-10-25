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

#include"atcoder/lazysegtree.hpp"

using S = long long;
using F = long long;

const S INF = 8e18;
const F ID = 8e18;

S op(S a, S b){ return std::min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return (f == ID ? x : f); }
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }

ll md=2000000000;

//メイン
int main(){
	ll n;
	cin>>n;
	vl w(n);
	rep(i,n)cin>>w[i];

	//mdが足されてなければ左で、左端座標がそれに加算されてる
	std::vector<S> v(n,n-1);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	vl nowl(n,0);

	ll q;
	cin>>q;
	while(q--){
		ll t;
		cin>>t;
		if(t==1){
			ll v;
			cin>>v;
			v--;

			ll tmp=seg.get(v);
			if(tmp>=md){
				tmp-=md;
				ll r=nowl[tmp]+w[tmp];
				nowl[v]=r-w[v];
			}else{
				nowl[v]=nowl[tmp];
			}
			
			seg.apply(0,v+1,v);
		}else if(t==2){
			ll v;
			cin>>v;
			v--;
			
			ll tmp=seg.get(v);
			if(tmp>=md){
				tmp-=md;
				ll r=nowl[tmp]+w[tmp];
				nowl[v]=r-w[v];
			}else{
				nowl[v]=nowl[tmp];
			}

			seg.apply(0,v+1,v+md);
		}else{
			ll x;
			cin>>x;
			ll mn=0,mx=n-1;
			if(x>=w.back()){
				cout<<0<<endl;
				continue;
			}
			while(mn!=mx){
				ll mid=mn+mx;
				mid/=2;

				ll tmp=seg.get(mid);
				if(tmp>=md){
					tmp-=md;
					ll r=nowl[tmp]+w[tmp];
					nowl[mid]=r-w[mid];
				}else{
					nowl[mid]=nowl[tmp];
				}

				if(nowl[mid]<=x&&x<nowl[mid]+w[mid]){
					mx=mid;
				}else{
					mn=mid+1;
				}
			}
			cout<<n-mn<<endl;
		}
	}

	return 0;
}
