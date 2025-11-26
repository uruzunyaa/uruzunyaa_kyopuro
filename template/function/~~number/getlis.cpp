#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 1000000000000000000LL

//LISを求める(狭義単調増加)
ll get_lis(vl a){
	ll ans=0;
	vl dp(a.size()+1,inf);
	dp[0]=-inf;
	rep(i,a.size()){
		auto it=upper_bound(dp.begin(),dp.end(),a[i]);
		*it=a[i];
		ans=max(ans,(ll)(it-dp.begin()));
	}
	return ans;
}

int main(){

	return 0;
}
