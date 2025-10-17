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

#include <atcoder/lazysegtree>

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

int main(){
    int n;
	cin>>n;
	vl a(n),mae(n,-1),hidari(n,0);
	unordered_map<ll,ll> tmp,r;
	rep(i,n){
		cin>>a[i];
		if(tmp.count(a[i]))mae[i]=tmp[a[i]];
		tmp[a[i]]=i;
		r[a[i]]++;
	}

	vl v(n,0);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	rep(i,n){
		if(mae[i]!=-1)seg.apply(mae[i],i,1);
		else seg.apply(0,n,1);
		hidari[i] = seg.prod(0,i);
	}

	ll ans=0;

	rep(i,n-1){
		r[a[i]]--;
		if(r[a[i]]==0)r.erase(a[i]);
		ans=max(ans,(ll)(hidari[i]+r.size()));
	}
	//vdbg(hidari);
	cout<<ans<<endl;
}


