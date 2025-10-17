//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	vl dp(2,0),sumdp(2,0);
	dp[0]=1;
	sumdp[0]=1;
	sumdp[1]=1;

	loop(i,2,n-1){
		ll tmp=sumdp[i-1];
		if(i-k-1>=0)tmp+=mod-sumdp[i-k-1];
		tmp%=mod;
		dp.push_back(tmp);
		sumdp.push_back((sumdp[i-1]+tmp)%mod);
	}
	ll ans=0;
	loop(i,max(0LL,n-k+1),n-1)ans+=dp[i];
	ans%=mod;
	cout<<ans<<endl;
	return 0;
}
