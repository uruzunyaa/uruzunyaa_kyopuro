#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define ll long long
int main(){
	//入力
	ll n,q;
	cin>>n>>q;
	vector<vector<ll>> c(n,vector<ll>(26));
	rep(i,n)rep(j,26)cin>>c[i][j];
	vector<string> w(q);
	rep(z,q)cin>>w[z];

	//dpテーブルを定義。
	vector<vector<ll>>dp(q+1,vector<ll>(n));
	rep(i,n)dp[0][i]=0;

	rep(i,q){
		//dp[i]の中で最も小さいものの累計コストを取り出す
		ll dpMin=*min_element(dp[i].begin(),dp[i].end());;
		
		rep(j,n){
			//コストを計算する。
			ll cost=0;
			rep(k,w[i].size())cost+=c[j][w[i][k]-'a'];

			//min(前と同じキーボード,コストが最も少ないキーボード)
			dp[i+1][j]=min(dp[i][j]+cost,dpMin+2*cost);
		}
	}
	ll mn=*min_element(dp[q].begin(),dp[q].end());
	cout<<mn<<endl;
	
	return 0;
}