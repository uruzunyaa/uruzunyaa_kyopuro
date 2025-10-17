#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vvvvl vector<vvvl>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i,m,n) for(ll i=m;i<=n;i++)

int main(){
    ll h,w;
	cin>>h>>w;
	vector<string> a(h);
	rep(i,h)cin>>a[i];

	vector<vector<pair<ll,ll>>> naname(h+w-1);
	rep(i,h)rep(j,w){naname[i+j].push_back({i,j});}

	//dpk[i][j][k][l]=左上を{i,j}右下を{k,l}とする、掛け算のみの最大値
	vvvvl dpk(h,vvvl(w,vvl(h,vl(w,0))));
	rep(i,h)rep(j,w){
		if((i+j)%2==1)continue;
		dpk[i][j][i][j] = 1;

		loop(z,i+j,h+w-2){
			rep(zz,naname[z].size()){
				ll k = naname[z][zz].first;
				ll l = naname[z][zz].second;
				if(k<i||l<j)continue;
				if(a[k][l]=='+')continue;

				//上
				if(k!=i){
					dpk[i][j][k][l]=max(dpk[i][j][k][l],dpk[i][j][k-1][l]);
				}
				//左
				if(l!=j){
					dpk[i][j][k][l]=max(dpk[i][j][k][l],dpk[i][j][k][l-1]);
				}

				if((k+l)%2==0)dpk[i][j][k][l]*=a[k][l]-'0';
				
				if(dpk[i][j][k][l]>1000000000000000){
					cout<<-1<<endl;
					return 0;
				}
			}
		}
	}

	vvl dp(h,vl(w,0));
	dp[0][0]=a[0][0]-'0';

	loop(z,1,h+w-2){
		rep(zz,naname[z].size()){
			ll i = naname[z][zz].first;
			ll j = naname[z][zz].second;
			
			if(a[i][j]=='*')continue;
			//上
			if(0!=i){
				dp[i][j]=max(dp[i][j],dp[i-1][j]);
			}
			//左
			if(0!=j){
				dp[i][j]=max(dp[i][j],dp[i][j-1]);
			}

		
			if((i+j)%2==0)dp[i][j]+=a[i][j]-'0';
			else continue;
			
			rep(k,i+1)rep(l,j+1){
				if((k+l)%2==1)continue;
				if(i==k&&j==l)continue;
				dp[i][j] = max(dp[i][j],dp[k][l]-(a[k][l]-'0')+dpk[k][l][i][j]);
			}
		}
	}

	if(dp[h-1][w-1]>1000000000000000){
		cout<<-1<<endl;
		return 0;
	}

	cout<<dp[h-1][w-1]<<endl;

	// rep(i,h){
	// 	rep(j,w)cout<<dp[i][j]<<" ";
	// 	cout<<endl;
	// }


}