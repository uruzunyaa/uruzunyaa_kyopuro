#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#include<atcoder/lazysegtree>

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
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];

	vl mae(n),usiro(n);
	vector<pair<ll,ll>> st;

	st.push_back({inf,-1});
	rep(i,n){
		while(st.back().first<a[i])st.pop_back();
		mae[i]=i-st.back().second;
		st.push_back({a[i],i});
	}

	st.clear();
	st.push_back({inf,n});
	rrep(i,n){
		while(st.back().first<=a[i])st.pop_back();
		usiro[i]=st.back().second-i;
		st.push_back({a[i],i});
	}

	vl v(n+2,0);
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> imos(v);
	
	rep(i,n){
		imos.apply(0,min(mae[i],usiro[i]),a[i]);
		imos.apply(max(mae[i],usiro[i]),mae[i]+usiro[i],-a[i]);
	}



	//vdbg(mae);
	//vdbg(usiro);

	ll tmp=0;
	rep(i,n){
		tmp+=imos.get(i);
		cout<<tmp<<endl;
	}
	return 0;
}
