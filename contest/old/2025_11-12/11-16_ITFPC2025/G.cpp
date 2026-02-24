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

#include<boost/multiprecision/cpp_int.hpp>
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

#include"atcoder/lazysegtree.hpp"

using S = long long;
using F = long long;

const S INF = 8e18;
const F ID = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return (f == ID ? x : f); }
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }


//メイン
int main(){
	string n;
	ll K;
	cin>>n>>K;

    std::vector<S> v(K,-1);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	//最大サイズを求める
	ll count = 0;
	ll zero = 0;
	rep(i,n.size()){
		if(n[i]=='0')zero++;
		else zero = 0;
		if(zero==2){
			count++;
			zero = 0;
		}
	}
	ll zeromin=n.size()-count;
	
	ll N=n.size()+1;
	n.insert(n.begin(),'0');
	vl mdlist(N);
	ll sums=0;
	rrep(i,N){
		mdlist[i]=power_mod(10,N-i-1)-sums;
		if(sums==0)mdlist[i]=0;
		mdlist[i]+=mod;
		mdlist[i]%=mod;

		sums+=power_mod(10,N-i-1)*(n[i]-'0');
		sums%=mod;	
	}
	ll mxk=n.size()-count;

	count = 0;
	zero = 0;
	
	rep(i,N){
		//i個目の桁を変更
		ll cnt=(N-i)/2;
		
		cnt+=i-count;
		if(i==0)cnt++;

		if(n[i]=='0')zero++;
		else zero = 0;
		if(zero==2){
			count++;
			zero = 0;
		}
		if(n[i]=='9')continue;
		if(cnt>K)continue;
		cnt--;
		seg.apply(cnt,K,mdlist[i]);
	}
	rep(i,K){
		if(i+1>=zeromin){
			cout<<0<<endl;
			continue;
		}
		cout<<seg.get(i)<<endl;
	}
	return 0;
}
