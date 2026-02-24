//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int

#include<atcoder/lazysegtree>

using S = pair<ll,ll>;
using F = long long;

const S INF = {8e18,8e18};

S op(S a, S b){ return std::min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ x.first+=f;return x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	vl a(n);
	ll ans=0;
	rep(i,n){
		cin>>a[i];
		a[i]-=n-i;
		ans+=i;
	}
	a[n-1]=inf;
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);

	rep(i,n-k){
		ll tmp=seg.prod(0,n);
		
	}
	return 0;
}
