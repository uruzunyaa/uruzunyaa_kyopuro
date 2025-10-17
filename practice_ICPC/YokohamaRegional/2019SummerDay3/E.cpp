#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define inf 1e18




int main() {
    ll n,k;
	cin>>n>>k;
	vl a(n),r(k),b(k);
	rep(i,n)cin>>a[i];
	rep(i,k)cin>>r[i];
	rep(i,k)cin>>b[i];

	sort(a.rbegin(),a.rend());
	sort(r.rbegin(),r.rend());
	sort(b.rbegin(),b.rend());
	

	vvvl dp(n+1,vvl(k+1,vl(k*50+1,inf)));
	dp[0][0][0]=0;

	ll redsum=0;
	ll blacksum=0;

	rep(i,k){
		redsum+=r[i];
		blacksum+=b[i];
	}
	ll sum=0;
	ll ans=inf;

	//dp[i][j][e]=配点の高い問題からi問既に考えて
	//そのうち、j問が赤の風船に割り当てられている
	//今までに赤に割り当てた風船の個数がeである状態
	//の風船の大きさ変更回数の最小値
	rep(i,n){
		rep(j,k+1){
			rep(e,k*50+1){
				if(dp[i][j][e]==inf)continue;
				ll useblack=i-j;
				if(useblack>k)continue;

				//赤の遷移
				if(j!=k){
					ll cost=a[i]-r[j];
					cost=max(0LL,cost);
					dp[i+1][j+1][e+a[i]]=min(dp[i+1][j+1][e+a[i]],dp[i][j][e]+cost);
				}
				//黒の遷移
				if(useblack!=k){
					ll cost=a[i]-b[useblack];
					cost=max(0LL,cost);
					dp[i+1][j][e]=min(dp[i+1][j][e],dp[i][j][e]+cost);
				}
			}
		}
		sum+=a[i];
	}

	rep(j,k+1){
		rep(e,k*50+1){
			ll tmp=sum-e;
			ll useblack=n-j;
			
			//黒を選び過ぎてる場合
			if(useblack>k)continue;

			//風船の総和が足りない場合は答えに記録しない
			if(e<=redsum&&tmp<=blacksum){
				ans=min(ans,dp[n][j][e]);
			}
			
		}
	}
	if(ans!=inf)cout<<ans<<endl;
	else cout<<-1<<endl;

	
}