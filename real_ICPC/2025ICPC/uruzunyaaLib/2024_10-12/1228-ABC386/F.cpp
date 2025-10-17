#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

//メイン
int main(){
	ll k;
	string s,t;
	cin>>k>>s>>t;

	//dp[i][j]=s[i]とt[i]まで進めるための最小の変更回数
	vector<map<ll,ll>> dp(s.size()+1);
	dp[0][0]=0;
	rep(i,s.size()){
		auto it=dp[i].begin();
		while(it!=dp[i].end()){
			ll j=it->first;
			ll tmp=it->second;
			if(tmp>k){
				it++;
				continue;
			}

			if(j!=t.size()&&s[i]==t[j]){
				if(dp[i+1].count(j+1))dp[i+1][j+1]=min(tmp,dp[i+1][j+1]);
				else dp[i+1][j+1]=tmp;
			}else if(j!=t.size()){
				if(dp[i+1].count(j+1))dp[i+1][j+1]=min(tmp+1,dp[i+1][j+1]);
				else dp[i+1][j+1]=tmp+1;
				
				if(dp[i].count(j+1))dp[i][j+1]=min(tmp+1,dp[i][j+1]);
				else dp[i][j+1]=tmp+1;
				
				if(dp[i+1].count(j))dp[i+1][j]=min(tmp+1,dp[i+1][j]);
				else dp[i+1][j]=tmp+1;
			}else{
				if(dp[i+1].count(j))dp[i+1][j]=min(tmp+1,dp[i+1][j]);
				else dp[i+1][j]=tmp+1;
			}
			it++;
		}
	}
	auto it=dp[s.size()].begin();

	while(it!=dp[s.size()].end()){
		ll cnt=t.size()-(it->first);
		ll tmp=it->second;
		if(cnt+tmp<=k){
			cout<<"Yes"<<endl;
			return 0;
		}
		it++;
	}		
	cout<<"No"<<endl;
	return 0;
}
