#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353
//#define mod 1000000007


//メイン
int main(){
	ll n,l;
	cin>>n>>l;

	ll sum=0;
	ll tmp = l-1;
	vl ok;
	rep(i,l/2){
		sum+=tmp;
		if(sum>200000)break;
		ok.push_back(sum);
		tmp-=2;
	}

	vl dp(200002,inf);
	dp[0]=0;

	rep(i,200000){
		rep(j,ok.size()){
			if(i+ok[j]>200000)break;
			dp[i+ok[j]]=min(dp[i]+1,dp[i+ok[j]]);
		}
	}
	rep(i,200001)if(dp[i]>=inf)dp[i]=-1;
	
	rep(i,n){
		ll a;
		cin>>a;
		cout<<dp[a]<<endl;
	}

	return 0;
}
