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

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }



vvl es(200001);
void solve(){
	ll n,k;
	cin>>n>>k;
	std::vector<S> v(n+1,0);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	
	rep(z,n){
		ll a;
		cin>>a;
		rep(j,es[a].size()){
			seg.apply(es[a][j],1);
		}
		seg.apply(1,(a/4)+1,1);
	}

	ll ans=1;
	loop(i,1,n){
		if(seg.get(i)>=n-k)ans=i;
	}
	cout<<ans<<endl;
	return;
}

//メイン
int main(){
	loop(i,1,200001){
		loop(j,1,3){
			if(i*j>200000)break;
			es[i*j].push_back(i);
		}
	}
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
