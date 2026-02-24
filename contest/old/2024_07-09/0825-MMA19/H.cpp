#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll n,m,k;
	cin>>n>>m>>k;
	vl ans(m,1);
	rep(i,n){
		vl tmp(m,0);
		loop(i,1,m){
			loop(j,1,m){
				if(abs((m/i)-(m/j))>k)continue;
				tmp[j-1]+=ans[i-1];
				tmp[j-1]%=mod;
			}
		}
	}
	ll sum=0;
	rep(i,m)sum+=ans[i],ans%=mod;
	cout<<ans<<endl;

	return 0;
}
