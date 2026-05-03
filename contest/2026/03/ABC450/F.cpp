#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#include <atcoder/lazysegtree>

using S = long long;
using F = long long;

S op(S a, S b){ return a+b; }
S e(){ return 0; }
S mapping(F f, S x){ return (f*x)%mod; }
F composition(F f, F g){ return (f*g)%mod; }
F id(){ return 1; }

int main(){
	ll n,m;
	cin>>n>>m;
	vvl g(n);
	rep(i,m){
		ll x,y;
		cin>>x>>y;
		x--,y--;
		g[y].push_back(x);
	}

	vector<S> v(n,0);
	v[0]=1;
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	

	rep(i,n){
		sort(g[i].begin(),g[i].end());
		for (auto val:g[i]){
			seg.apply(0,val,2);
			ll tmp=seg.prod(val,i+1);
			tmp+=seg.get(i);
			tmp%=mod;
			seg.set(i,tmp);
		}
	}
	cout<<seg.get(n-1)<<endl;
}