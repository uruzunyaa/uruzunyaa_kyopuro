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
#include<atcoder/segtree>
pair<ll,ll> e(){return {0,0};}
pair<ll,ll> op(pair<ll,ll> a,pair<ll,ll> b){
	pair<ll,ll> ans;
	return ans;
}

//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	vector<pair<ll,ll>> a(n);
	rep(i,n)cin>>a[i].first;

	atcoder::segtree<pair<ll,ll>,op,e> seg(a);
	return 0;
}
