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
	string n;
	cin>>n;
	ll kyoukai=inf;
	rep(i,n.size())if(n[0]!=n[i]){
		kyoukai=i;
		break;
	}

	vvl dp(n.size(),vl(4,0));
	
	if(kyoukai==inf){
		dp[0][0]+=n[0]-'0';
	}else if(n[kyoukai]<n[0]){
		loop(i,1,kyoukai)dp[i][1]+=n[kyoukai]-'0';
	}else{
		dp[0][0]+=n[0]-'0';
		ll bigcnt=n[kyoukai]-n[0]-1;
		dp[kyoukai-1][0]+=bigcnt;
		dp[kyoukai][0]+='9'-n[kyoukai];
	}

	loop(i,1,n.size()-1)dp[i][0]+=81;

	dp[0][0]+=(n[0]-'0'-1)*9;

	if(kyoukai!=inf){
		ll sim=0;
		ll mx=max(n[kyoukai],n[0]);
		ll mn=min(n[kyoukai],n[0]);
		loop(i,1,n.size()-1){
			
			if(mx<n[i]){
				ll tmp=sim;
				
				dp[i][tmp]++;
				
				tmp++;
				if(tmp==4)tmp=2;
				
				dp[i][tmp]++;
				break;
			}else if(mn<n[i]&&n[i]<mx){
				ll tmp=sim;
				if(n[i]==n[i-1])tmp++;
				if(tmp==4)tmp=2;
				dp[i][tmp]++;
				break;
			}else if(n[i]<mn){
				break;
			}else if(n[i]==mx){
				ll tmp=sim;
				if(n[i]==n[i-1])tmp++;
				if(tmp==4)tmp=2;
				dp[i][tmp]++;
			}

			if(n[i]!=n[i-1])sim++;
			if(sim==4)sim=2;
		}
	}


	rep(i,n.size()-1){
		//境界値ではないものの遷移
		rep(j,4){
			ll next=j+1;
			if(next==4)next=2;
			dp[i+1][j]+=dp[i][j];
			dp[i+1][next]+=dp[i][j];
			dp[i+1][j]%=mod;
			dp[i+1][next]%=mod;
		}
	}
	
	

	cout<<dp[n.size()-1][3]<<endl;

	
	return 0;
}
