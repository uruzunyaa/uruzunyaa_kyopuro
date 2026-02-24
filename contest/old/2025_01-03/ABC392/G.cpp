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
//#define mod 998244353LL
//#define mod 1000000007LL
#include <atcoder/all>
//using namespace atcoder;
//メイン
int main(){
	ll n;
	cin>>n;
	vl t(1000001,0);
	rep(i,n){
		ll tt;
		cin>>tt;
		t[tt]++;
	}
	vl s=atcoder::convolution_ll(t,t);
	ll ans=0;
	loop(i,1,1000000){
		ans+=t[i]*(s[i*2]/2);
	}

	cout<<ans<<endl;
	return 0;
}
