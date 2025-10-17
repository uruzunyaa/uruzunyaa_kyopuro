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
ll solve(){
	ll n;
	string s;
	cin>>n;
	if(n==0)return 1;
	cin>>s;
	//7個あったら確実に可能なので、不可能なら7を出力しに行く。
	vector<vector<bool>> dp(7,vector<bool>(n+1,false));
	dp[0][0]=true;

	loop(a,0,n/6){
		loop(i,0,n)dp[1][i]=dp[0][i];
		loop(i,a,n)if(dp[0][i-a])dp[1][i]=true;
		loop(b,a,(n-a)/5){
			loop(i,0,n)dp[2][i]=dp[1][i];;
			loop(i,b,n)if(dp[1][i-b])dp[2][i]=true;
			loop(c,b,(n-a-b)/4){
				loop(i,0,n)dp[3][i]=dp[2][i];
				loop(i,c,n)if(dp[2][i-c])dp[3][i]=true;
				loop(d,c,(n-a-b-c)/3){
					loop(i,0,n)dp[4][i]=dp[3][i];
					loop(i,d,n)if(dp[3][i-d])dp[4][i]=true;
					loop(e,d,(n-a-b-c-d)/2){
						loop(i,0,n)dp[5][i]=dp[4][i];
						loop(i,e,n)if(dp[4][i-e])dp[5][i]=true;
						ll f=n-a-b-c-d-e;
						loop(i,0,n)dp[6][i]=dp[5][i];
						loop(i,f,n)if(dp[5][i-f])dp[6][i]=true;
						bool flag=true;
						loop(i,0,n)if(!dp[6][i]&&s[i]=='o')flag=false;
						if(flag){
							ll ans=1;
							if(a!=0)ans++;
							if(b!=0)ans++;
							if(c!=0)ans++;
							if(d!=0)ans++;
							if(e!=0)ans++;
							cout<<ans<<endl;
							return 0;
						}
					}
				}
			}
		}
	}
	cout<<7<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}