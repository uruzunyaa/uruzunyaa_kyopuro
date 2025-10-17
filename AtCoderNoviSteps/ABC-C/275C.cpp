#include<bits/stdc++.h>
using namespace std;
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
	ll ans=0;
	vector<string>s(9);
	rep(i,9)cin>>s[i];
	rep(i,9){
		rep(j,9){
			rep(k,9){
				rep(l,9){
					if(i==k&&j==l)continue;
					if(s[i][j]=='.')continue;
					if(s[k][l]=='.')continue;
					ll dx=k-i;
					ll dy=l-j;
					if(0<=i+dy&&i+dy<9&&0<=k+dy&&k+dy<9&&0<=j-dx&&j-dx<9&&0<=l-dx&&l-dx<9){
						if(s[i+dy][j-dx]=='#'&&s[k+dy][l-dx]=='#')ans++;
					}
					if(0<=i-dy&&i-dy<9&&0<=k-dy&&k-dy<9&&0<=j+dx&&j+dx<9&&0<=l+dx&&l+dx<9){
						if(s[i-dy][j+dx]=='#'&&s[k-dy][l+dx]=='#')ans++;
					}
				}
			}
		}
	}
	ans/=8;
	cout<<ans<<endl;
	return 0;
}
