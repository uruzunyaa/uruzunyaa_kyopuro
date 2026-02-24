//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


//メイン
int main(){
	ll t,m;
	cin>>t>>m;

	vvl dp(5001,vl(5001));
	rep (i,5001)dp[i][0] = 1;
	rep (i,5001)dp[i][i] = 1;
	loop (i,1,5000){
		loop (j,1,min((ll)i-1,(ll)5000)) {
			//nCr= n-1Cr-1 + n-1Cr
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
			dp[i][j]%=m;
		}
	}

	rep(z,t){
		ll n;
		cin>>n;
		vl c(n);
		rep(i,n)cin>>c[i];
		ll ans=1;
		ll sum=0;
		rep(i,n){
			sum+=c[i];
			ans*=dp[sum][c[i]];
			ans%=m;
		}
		cout<<ans<<endl;
	}
	return 0;
}
