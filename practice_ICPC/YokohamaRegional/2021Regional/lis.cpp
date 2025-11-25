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