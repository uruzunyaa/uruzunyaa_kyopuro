//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
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

#include"atcoder/lazysegtree.hpp"

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

void solve(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	vl v=a;
	rep(i,n){
		if(i%2==0)v[i]=-inf;
		v[i]*=2;
		v[i]+=i;
	}
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	ll ans=n-1;
	ans/=2;
	ans*=2;
	rep(i,n){
		if(i%2==0){
			ans=max(ans,(-a[i]*2)+(seg.prod(0,n)));
		}
		seg.apply(0,i+1,1);
		seg.apply(i+1,n,-1);
	}

	rep(i,n){
		if(i%2==0)ans+=a[i];
		else ans-=a[i];
	}
	cout<<ans<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();	
	return 0;
}
