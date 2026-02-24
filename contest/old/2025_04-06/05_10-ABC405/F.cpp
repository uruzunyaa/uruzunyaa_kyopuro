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

#include <atcoder/lazysegtree>

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl v(2*n,0);
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	vvl ab(2*n);
	vvl ba(2*n);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		ab[a].push_back(b);
		ba[b].push_back(a);
		seg.apply(a,b,1);
	}
	ll q;
	cin>>q;
	vector<vector<pair<ll,ll>>> cd(2*n);
	rep(i,q){
		ll c,d;
		cin>>c>>d;
		c--,d--;
		cd[c].push_back({d,i});
	}
	vl ans(q);

	rep(i,2*n){
		if(i%2==0){
			rep(j,cd[i].size()){
				ans[cd[i][j].second]=seg.get(cd[i][j].first);
			}
		}else{
			rep(j,ab[i].size()){
				seg.apply(i,ab[i][j],-1);
				seg.apply(ab[i][j],2*n,1);
			}
			rep(j,ba[i].size()){
				seg.apply(i,2*n,-1);
			}
		}
	}

	rep(i,q)cout<<ans[i]<<endl;
	return 0;
}
