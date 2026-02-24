#pragma GCC optimize("O3")
#include<bits/stdc++.h>
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

#include"atcoder/lazysegtree.hpp"

const ll ID = inf;

ll op(ll a, ll b){ return std::min(a, b); }
ll e(){ return inf; }
ll mapping(ll f, ll x){ return (f == ID ? x : f); }
ll composition(ll f, ll g){ return (f == ID ? g : f); }
ll id(){ return ID; }

int main(){
	ll h,w,n;
    cin>>h>>w>>n;
	vvl var;
	rep(i,n){
		ll r,c,l;
		cin>>r>>c>>l;
		vl t;
		t.push_back(r);
		t.push_back(c-1);
		t.push_back(l+c-1);
		t.push_back(i);
		var.push_back(t);
	}
	sort(var.rbegin(),var.rend());
	vl ans(n);
    vl tmp(w,h+1);
    atcoder::lazy_segtree<ll, op, e, ll, mapping, composition, id> seg(tmp);
	//rep(i,w)cout<<seg.get(i)<<endl;
	
	rep(i,n){
		ll takasa=seg.prod(var[i][1],var[i][2])-1;
		ans[var[i][3]]=takasa;
		seg.apply(var[i][1],var[i][2],takasa);	
	}
	rep(i,n)cout<<ans[i]<<endl;
}