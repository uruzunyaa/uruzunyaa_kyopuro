#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for(long long i=0;i<(ll)n;i++)
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
void solve(){
	ll n,k;
	cin>>n>>k;
	k*=2;

	vl a(k);
	rep(i,k)cin>>a[i];

	//開き括弧の余りの数。
	ll m=0;
	
	vector<map<ll,ll>> dp(k+1);
	dp[0][0]=n;
	rep(i,k){
		if(dp[i].begin()->second<=a[i]){
			//開き括弧の個数が多い方にはみ出る場合
			ll hasuu=a[i]-dp[i].begin()->second;
			dp[i+1][dp[i].begin()->first+1]=n-hasuu;
			if(n!=hasuu)dp[i+1][dp[i].begin()->first+3]=hasuu;
		}else{
			ll hasuu=dp[i].begin()->second-a[i];
			dp[i+1][dp[i].begin()->first+1]=n-hasuu;
			dp[i+1][dp[i].begin()->first-1]=hasuu;
		}
		if(dp[i+1].begin()->first<0){
			cout<<"No"<<endl;
			return;
		}
	}
	if(dp[k][0]==n)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
