#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for(ll i = a; i <= (ll)b; ++i)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000000000000LL
int main() {
	ll n; cin >> n;
	vector<string> g(3);
	rep(i, 3) {
		cin >> g[i];
	}

	vl dp(9,-inf);
	dp[0]=0;
	vvl oks(9);
	oks[1]={0,1,2};
	oks[3]={0,1,2};
	oks[4]={0,2};
	oks[5]={0,1,2};
	oks[7]={0,1,2};

    rep(i,n){
		vl ndp(9,-inf);
		rep(j,9){
			bool f=false;
			rep(k,oks[j].size()){
				if(g[oks[j][k]][i]=='#')f=true;
			}
			if(f)continue;
			
			//転移しない遷移
			if(j!=3&&j!=5){
				ndp[j]=max(ndp[j],dp[j]+(ll)oks[j].size());
			}

			//1個先へ進む遷移
			if(j!=0){
				ndp[j]=max(ndp[j],dp[j-1]+(ll)oks[j].size());
			}
		}
		swap(dp,ndp);
		rep(j,9)cout<<dp[j]<<" ";
		cout<<endl;
	}
	ll ans=max(dp[7],dp[8]);
	ans=max(ans,-1LL);
	cout<<ans<<endl;
    return 0;
}