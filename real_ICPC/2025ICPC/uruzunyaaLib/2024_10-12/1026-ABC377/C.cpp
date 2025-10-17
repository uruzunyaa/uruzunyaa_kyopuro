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

vl dx={0,-1,-1,1,1,-2,-2,2,2};
vl dy={0,2,-2,2,-2,1,-1,1,-1};

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	set<pair<ll,ll>> s;
	rep(z,m){
		ll a,b;
		cin>>a>>b;
		rep(i,9){
			ll x=a+dx[i];
			ll y=b+dy[i];
			if(1<=x&&x<=n&&1<=y&&y<=n){
				s.insert({x,y});
			}
		}
	}
	cout<<n*n-s.size()<<endl;
	return 0;
}
