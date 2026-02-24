#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 1000000007LL

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n+1);
	ll sum=n*10;
	loop(i,1,n)cin>>a[i];
	vvl dp(n+1,vl(sum*2+1,0));
	dp[0][0+sum]=1;
	
	ll ans=1;
	//i個目の数字を選んでだ時
	loop(i,1,n){
		//j個目を前回数列更新位置として、
		rep(j,i){
			//j個目の時点での累積和がkであるもの
			//ここのループ範囲に注意、要素外参照するよ。
			loop(k,-sum+10,sum-10){
				if(k==0){
					set<ll> s;
					s.insert(0);
					loop(l,j+1,i-1){
						if(s.count(a[l]))continue;
						s.insert(a[l]);
						dp[i][k+sum+a[i]+a[l]]+=dp[j][k+sum];
						dp[i][k+sum+a[i]+a[l]]%=mod;
						ans+=dp[j][k+sum];
						ans%=mod;
					}
				}else{
					dp[i][k+sum+a[i]]+=dp[j][k+sum];
					dp[i][k+sum+a[i]]%=mod;
					ans+=dp[j][k+sum];
					ans%=mod;
				}
			}
		}
		
	}
	//vvdbg(dp);
	cout<<ans<<endl;
	
	return 0;
}
