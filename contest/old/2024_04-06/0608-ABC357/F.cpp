//#pragma GCC optimize("O3")
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
#define Yes cout<<"Yes"<<endl;return 0;
#define No cout<<"No"<<endl;return 0;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

struct S{
    ll value;
    ll suma;
	ll sumb;
	ll size;
};
using F = pair<ll,ll>;

S op(S x, S y){
	S ans;
	ans.value=(x.value+y.value)%mod;
	ans.suma=(x.suma+y.suma)%mod;
	ans.sumb=(x.sumb+y.sumb)%mod;
	ans.size=x.size+y.size;
	return ans;
}
S e(){ return {0, 0 ,0, 0}; }
S mapping(F f, S x){
	S ans;
	ans.value=(x.value + f.first*x.sumb + f.second*x.suma + (f.first*f.second%mod)*(x.size%mod))%mod;
	ans.suma=(x.suma+f.first*x.size)%mod;
	ans.sumb=(x.sumb+f.second*x.size)%mod;
	ans.size=x.size;
	return ans; 
}
F composition(F f, F g){ return {(f.first+g.first)%mod,(f.second+g.second)%mod}; }
F id(){ return {0,0}; }

#include<atcoder/lazysegtree>
//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	vector<S> v(n);
	rep(i,n){
		ll a;
		cin>>a;
		v[i].suma=a;
	}
	rep(i,n){
		ll b;
		cin>>b;
		v[i].sumb=b;
		v[i].value=v[i].suma*v[i].sumb;
		v[i].size=1;
	}
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	while(q--){
		ll t;
		cin>>t;
		if(t==1){
			ll l,r,x;
			cin>>l>>r>>x;
			l--;
			seg.apply(l,r,{x,0});
		}else if(t==2){
			ll l,r,x;
			cin>>l>>r>>x;
			l--;
			seg.apply(l,r,{0,x});
		}else{
			ll l,r;
			cin>>l>>r;
			l--;
			cout<<seg.prod(l,r).value%mod<<endl;
		}
	}
	return 0;
}
