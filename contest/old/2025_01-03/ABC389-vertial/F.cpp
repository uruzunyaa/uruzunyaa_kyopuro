#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#include<atcoder/lazysegtree>
using namespace std;
using namespace atcoder;
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

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

// 区間 [x, j) の最大値が v 以下であるような最大の j を求めたい
ll val;
bool func(ll seg_val) { return seg_val <= val; }

//メイン
int main(){
	vl v(500001,0);
	rep(i,500001)v[i]=i;
	lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	
	ll n;
	cin>>n;
	rep(i,n){
		ll l,r;
		cin>>l>>r;
		val = l-1;
		ll mn=seg.max_right<func>(0);
		val = r;
		ll mx=seg.max_right<func>(0);
		//cout<<mn<<" "<<mx<<endl;
		seg.apply(mn,mx,1);
	}
	ll q;
	cin>>q;
	while(q--){
		ll x;
		cin>>x;
		cout<<seg.get(x)<<endl;
	}

	return 0;
}
