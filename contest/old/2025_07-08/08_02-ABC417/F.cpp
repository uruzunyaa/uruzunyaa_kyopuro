#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

#include"atcoder/lazysegtree.hpp"

struct S{
    ll value;
    int size;
};
using F = long long;

const F ID = 8e18;

S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){
    if(f != ID) x.value = f*x.size;
    return x;
}
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }

// nのk乗をmodで割った余りを計算(modはdefineで定義想定)
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
    std::vector<S> v(n, {0, 1});
	rep(i,n)cin>>v[i].value;
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	rep(i,m){
		ll l,r;
		cin>>l>>r;
		l--;
		ll sm=seg.prod(l,r).value;
		
		sm%=mod;
		sm*=power_mod(r-l,mod-2);
		sm%=mod;
		seg.apply(l,r,sm);
	}
	rep(i,n){cout<<seg.get(i).value%mod<<" ";}
	cout<<endl;
}