#include<bits/stdc++.h>
using namespace std;
#define ll int
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 1e9
#define mod 1000000007LL
#define eps 0.000000001


//メイン
int main(){
	ll n;
	string s;
	cin>>n>>s;
	deque<ll> dp,ndp;
	rep(i,n)dp.push_back(1);

	rep(i,n-1){
		ll sum=0;
		if(s[i]=='<'){
			rep(j,n-i-1){
				sum+=dp[j];
				sum%=mod;
				ndp.push_back(sum);
			}
		}else{
			rrep(j,n-i-1){
				sum+=dp[j+1];
				sum%=mod;
				ndp.push_front(sum);
			}
		}
		swap(dp,ndp);
		ndp=deque<ll>();
	}
	cout<<dp.front()<<endl;
	return 0;
}
