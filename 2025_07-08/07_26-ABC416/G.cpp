#pragma GCC optimize("O3")
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
#define mod 998244353LL
#define eps 0.000000001


//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	unordered_set<string> s,t;
	rep(i,n){
		string ss;
		cin>>ss;
		s.insert(ss);
		loop(j,1,ss.size()){
			t.insert(ss.substr(0,j));
		}
	}

	string ans;
	vl dp(1,0);

	loop(i,1,10){
		vl tmp;
		loop(h,1,min(i,10)){
			if(dp[i-h]==-inf)continue;
			tmp.push_back(h);
		}
		rep(j,26){
			//文字tmpを置けるか判定する。
			ans.push_back('a'+j);
			
			bool f=false;
			rep(h,tmp.size()){
				if(t.count(ans.substr(i-tmp[h]))){
					f=true;
					break;
				}
			}
			if(f)break;
			ans.pop_back();
		}
		dp.push_back(-inf);
		
		rep(h,tmp.size()){
			if(s.count(ans.substr(i-tmp[h]))){
				dp[i]=max(dp[i],dp[i-tmp[h]]+1);
				if(dp[i]==k){
					cout<<ans<<endl;
					return 0;
				}
			}
		}
	}

	vector<bool> bk(26,false);
	rep(i,10)bk[ans[i]-'a']=true;
	vl kouho;
	rep(i,26)if(bk[i])kouho.push_back(i);


	loop(i,11,10*k){
		vl tmp;
		loop(h,1,min(i,10)){
			if(dp[i-h]==-inf)continue;
			tmp.push_back(h);
		}
		rep(j,kouho.size()){
			//文字tmpを置けるか判定する。
			ans.push_back('a'+kouho[j]);
			
			bool f=false;
			rep(h,tmp.size()){
				if(ans.substr(0,tmp[h])==ans.substr(i-tmp[h])){
					f=true;
					break;
				}
			}
			if(f)break;
			ans.pop_back();
		}
		dp.push_back(-inf);
		
		rep(h,tmp.size()){
			if(ans.substr(0,tmp[h])==ans.substr(i-tmp[h])&&dp[tmp[h]]!=-inf){
				dp[i]=max(dp[i],dp[i-tmp[h]]+dp[tmp[h]]);
				if(dp[i]==k){
					cout<<ans<<endl;
					return 0;
				}
			}
		}
	}
	return 0;
}
