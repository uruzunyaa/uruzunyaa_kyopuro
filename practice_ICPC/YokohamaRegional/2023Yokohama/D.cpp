#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= (ll)b; ++i)
#define vl vector<ll>
#define vvl vector<vl>
int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};

string mymin(string a,string b){
	if(a.size()<b.size())return a;
	if(a.size()>b.size())return b;
	return min(a,b);
}

int main(){
	string s;
	cin>>s;
	ll n=s.size();
	vector<vector<string>> dp(n+1,vector<string>(n+1,string(n+1,'.')));
	
	rep(j,n){
		dp[1][j]=s[j];
	}
	loop(i,1,n){
		rep(j,n-i+1){
			//マージフェーズ
			loop(k,1,i-1){
				dp[i][j]=mymin(dp[i][j],dp[k][j]+dp[i-k][j+k]);
			}

			//圧縮フェーズ
			loop(k,1,min(((n-j)/i)-1,8LL)){
				bool f=true;
				rep(l,i){
					if(s[j+l]!=s[j+l+k*i]){
						f=false;
						break;
					}
				}
				if(f){
					dp[i*(k+1)][j]=mymin(dp[i*(k+1)][j],to_string(k+1)+"("+dp[i][j]+")");
				}else{
					break;
				}
				
			}
		}
		
	}

	cout<<dp[n][0]<<endl;
	return 0;
}