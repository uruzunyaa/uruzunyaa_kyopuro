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
ll solve(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	vl dp(n+1,inf);
	dp[0]=0;
	vl inc(n);

	vl rdp(n+1,0);
	rdp[0]=inf;
	vl rinc(n);

	rep(i,n){
		ll it=lower_bound(dp.begin(),dp.end(),a[i])-dp.begin();
		dp[it]=a[i];
		inc[i]=it;

		ll rit=upper_bound(rdp.rbegin(),rdp.rend(),a[n-i-1])-rdp.rbegin()-1;
		
		rdp[n-rit]=a[n-i-1];
		rinc[n-i-1]=n-rit;
	}
	ll lis=lower_bound(dp.begin(),dp.end(),inf)-dp.begin()-1;

	// vdbg(inc);
	// vdbg(rinc);
	
	vl ans;
	rep(i,n)if(inc[i]+rinc[i]==lis+1)ans.push_back(i+1);

	cout<<ans.size()<<endl;
	vdbg(ans);
	return 0;
}

int main(){
	ll t;
	cin>>t;
	rep(i,t){
		ll tmp=solve();
	}
	return 0;
}