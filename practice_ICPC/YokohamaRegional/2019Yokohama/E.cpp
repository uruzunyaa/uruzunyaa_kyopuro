#include <bits/stdc++.h>
using namespace std;
using ll = unsigned int;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i,m, n) for(ll i = m; i <= n; ++i)
#define vl vector<ll>
#define vvl vector<vl>
#define mod 1000000007

int main(){
    ll n,m;
	cin>>n>>m;
	vl a(n);
	rep(i,n)cin>>a[i];
	
	set<ll> st;
	loop(i,1,n)st.insert(i);
	ll mx=0;

	//[残りのMIN]>[使った奴のMAX]なら2通り
	//[残りのMIN]<[使った奴のMAX]なら以下の場合分け
	//[使う奴]==[残りのMIN]
	//上じゃないのに[使う奴]<[使った奴のMAX]答えを0通りにして終わり
	//その他

	//dp[i][j][k]=i番目の数字で、左がj個の高さでkがどっちが最大か
	vvl dp(1,vl(2,0));
	dp[0][0]=1;
	//dp[0][0][1]=1;

	rep(i,n){
		vvl ndp=vvl(i+2,vl(2,0));
		rep(j,i+1){
			if(*st.begin()>mx){
				//[残りのMIN]>[使った奴のMAX]なら左右2通り
				
				//左に置く場合
				ndp[j+1][0]+=dp[j][0]+dp[j][1];

				//右に置く場合
				ndp[j][1]+=dp[j][0]+dp[j][1];
			}else if(a[i]==*st.begin()){
				//[使う奴]==[残りのMIN](使う奴は最大でない)

				//左に置く場合
				ndp[j+1][1]+=dp[j][1];

				//右に置く場合
				ndp[j][0]+=dp[j][0];
			}else if(mx<a[i]){
				//[使った奴のMAX]<[使う奴](最小値は残さなきゃいけない)

				//左に置く場合
				ndp[j+1][0]+=dp[j][0];

				//右に置く場合
				ndp[j][1]+=dp[j][1];
			}else{
				//[残りのMIN]<[使う奴]<[使った奴のMAX]答えを0通りにして終わり
				cout<<0<<endl;
				return 0;
			}
			
			ndp[j][0]%=mod;
			ndp[j][1]%=mod;
			ndp[j+1][0]%=mod;
			ndp[j+1][1]%=mod;
		}
		st.erase(a[i]);
		mx=max(a[i],mx);
		swap(dp,ndp);
	}
	ll ans=0;
	rep(i,n+1){
		if(max(i,n-i)>m)continue;
		ans+=dp[i][0];
		ans+=dp[i][1];
	}
	ans%=mod;
	cout<<ans<<endl;
}