#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i ,m, n) for (ll i = m; i <= n; ++i)
#define pll pair<ll,ll>
#define vl vector<ll>
#define vvl vector<vl>
#define inf 100000000000000000LL

int main() {
	ll n;
	string s;
	cin>>n>>s;
	s.push_back('+');

	//dp[i][j]=i文字目まで見ていて、そのi文字目が＋となっている時。
	//j文字変更している時の合計の最小値
	vvl dp(s.size()+1,vl(s.size(),inf));
	dp[0][0]=0;
	

	rep(i,s.size()){
		rep(j,s.size()){
			if(dp[i][j]==inf)continue;

			//何文字先に遷移するか、+を置く所までで最大11文字以上一気には置けない。
			loop(k,2,11){
				if(i+k>s.size())break;

				//何文字変更するか
				loop(l,0,k){
					//残り変更数,整数部分
					ll cnt=l;
					string tmp=s.substr(i,k-1);

					//最初と最後は特殊なので前処理
					if(s[i+k-1]!='+')cnt--;
					if(tmp[0]=='+'){
						cnt--;
						if(k==2)tmp[0]='0';
						else tmp[0]='1';
					}
					if(tmp[0]=='0'&&k!=2){
						cnt--;
						tmp[0]='1';
					}

					//2文字目以降の+の残りを処理
					loop(m,1,k-2){
						if(tmp[m]=='+'){
							tmp[m]='0';
							cnt--;
						}
					}
					
					//変更文字数が足りない場合,continue
					if(cnt<0)continue;

					//変更がまだ可能な場合、1文字目だけは特殊処理
					if(cnt!=0){
						if(k==2){
							if(tmp[0]!='0'){
								cnt--;
								tmp[0]='0';
							}
						}else{
							if(tmp[0]!='1'){
								cnt--;
								tmp[0]='1';
							}
						}
					}

					//2文字目以降を貪欲に0に変更
					loop(m,1,k-2){
						if(cnt==0)break;
						if(tmp[m]!='0'){
							tmp[m]='0';
							cnt--;
						}
					}
					
					//変更文字数が余ってる場合不適
					if(cnt!=0)break;

					dp[i+k][j+l]=min(dp[i+k][j+l],dp[i][j]+stoll(tmp));
					
				}
			}
		}
	}

	//出力
	rep(j,s.size()){
		if(dp[s.size()][j]<=n){
			cout<<j<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
    return 0;
}