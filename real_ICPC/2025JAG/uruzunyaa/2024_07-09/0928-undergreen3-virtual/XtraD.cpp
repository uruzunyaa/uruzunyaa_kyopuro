#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#include<atcoder/lazysegtree>
using namespace std;
using namespace atcoder;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	if(n>162){
		cout<<k<<endl;
		return 0;
	}
	//dp[i][f][j]=i番目の桁がj以下であり、現在の桁和がfであるような物の数。
	vector<vvl> dp(1,vvl(n+1,vl(10,0)));
	dp[0][0][9]=1;
	rep(i,inf){
		vvl tmp=vvl(n+1,vl(10,0));
		ll sum=0;
		rep(f,n+1){
			rep(j,10){
				if(j==0)tmp[f][0]=dp[i][f][9];
				else {
					tmp[f][j]=tmp[f][j-1];
					if(f-j<0)continue;
					tmp[f][j]+=dp[i][f-j][9];
				}
				if(sum<=1000000000000000000)sum+=dp[i][f-j][9];
			}
		}
		dp.push_back(tmp);
		if(sum>k)break;
	}
	for(ll i=dp.size()-1;i>0;i--){
		vl sum(10,0);
		rep(j,10){
			rep(f,n+1){
				if(sum[j]<=1000000000000000000)sum[j]+=dp[i][f][j];
			}
			if(sum[j]>k){
				if(j==0){
					cout<<0;
					break;
				}
				k-=sum[j-1];
				n-=j;
				cout<<j;
				break;
			}
		}
	}
	cout<<endl;
	return 0;
}
