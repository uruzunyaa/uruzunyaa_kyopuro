#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL

//2つの文字列の編集距離を求める。O(|S|×|T|)
ll edit_dist(string s,string t){
	vvl dp(s.size()+1,vl(t.size()+1,inf));
	dp[0][0]=0;

	rep(i,s.size())rep(j,t.size()){
		ll cost=1;
		if(s[i]==t[j])cost=0;
		dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+cost);
		dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
		dp[i][j+1]=min(dp[i][j+1],dp[i][j]+1);
	}
	rep(i,s.size())dp[i+1][t.size()]=min(dp[i+1][t.size()],dp[i][t.size()]+1);
	rep(j,t.size())dp[s.size()][j+1]=min(dp[s.size()][j+1],dp[s.size()][j]+1);
	return dp[s.size()][t.size()];
}

//メイン
int main(){
	return 0;
}
