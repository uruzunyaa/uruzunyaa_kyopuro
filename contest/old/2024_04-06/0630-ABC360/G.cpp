#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	//aの最後にバカでかい値を補う
	a.push_back(inf/2);

	//dp[i]=i個の増加部分列を現在持つものの、{数値,変更可能性}
	vector<pair<ll,ll>> dp(n+2,{inf,0});
	
	//一回の操作を記録
	pair<ll,ll> tmp={-inf,0};
	ll tmpindex=0;
	dp[0]=tmp;

	//1回前のdp配列そのもの
	vector<pair<ll,ll>> dp2(n+2,{inf,0});

	rep(i,n+1){
		//通常の最長増加部分列処理
		ll index=lower_bound(dp.begin(),dp.end(),make_pair(a[i],-inf))-dp.begin();
		dp[index]={a[i],dp[index-1].second};

		//index2つ以上前の状態で、2以上の差がついているならフラグをtrueへ変更
		if(dp2[index-1].first<=a[i]-2)dp[index].second=1;

		//index2以上前を現在の物へ変更
		dp2[tmpindex]=tmp;

		//現在の行った変更を、次回の変更分として保管
		tmp=dp[index];
		tmpindex=index;
	}
	
	//最後に無限を補ったので、それを除く必要がある。
	//よってinf以外の最大のindex+そのsecond-1で答え。
	ll ans=0;
	rep(i,n+2){
		if(dp[i].first!=inf){
			ans=i+dp[i].second-1;
		}
	}

	cout<<ans<<endl;
	return 0;
}
