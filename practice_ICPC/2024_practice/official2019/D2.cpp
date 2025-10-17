// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#ifdef DEBUG
#include "cpp-dump/dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#endif
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
//#define mod 1000000007LL

//2019-D
ll solve(){
	ll n,m;
	cin>>n>>m;
	if(n==0)return 1;

	vl a(n+1),b(n+1);
	loop(i,1,n)cin>>a[i];
	//b[i]-a[i](mod m)に変換
	loop(i,1,n){
		cin>>b[i];
		b[i]-=a[i];
		if(b[i]<0)b[i]+=m;
	}
	b[0]=0;

	//dp[i][j]=i番目までのカウンタ揃え、i番目のカウンタをj周余分に回す時の最小操作回数
	vector<vector<ll>> dp(n+1,vl(n+1,inf));
	dp[0][0]=0;
	rep(i,n){
		if(b[i]<b[i+1]){
			//遷移先の方が大きい時は左下と左から遷移する
			rep(j,n){
				dp[i+1][j]=min(dp[i][j]+b[i+1]-b[i],dp[i][j+1]);
			}
			dp[i+1][n]=dp[i][n]+b[i+1]-b[i];
		}else if(b[i]>b[i+1]){
			//遷移元の方が大きい時は左上と左から遷移する
			dp[i+1][0]=dp[i][0];
			rep(j,n){
				dp[i+1][j+1]=min(dp[i][j]+m+b[i+1]-b[i],dp[i][j+1]);
			}
		}else {
			//同数の時は前回の結果を引き継ぐ
			dp[i+1]=dp[i];
		}
	}
	//最後まで余分な周回を余らせても意味がないので余ってない時が答え
	cout<<dp[n][0]<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}