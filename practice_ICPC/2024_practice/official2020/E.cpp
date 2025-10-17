#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 1000000007LL
bool solve(){
	ll h,w;
	cin>>h>>w;
	if(h==0)return false;

	vector<string> a(h);
	rep(i,h)cin>>a[i];

	vector<string> s(((h+3)/4)*4,string(w,'#'));
	rep(i,h)rep(j,w)s[i][j]=a[i][j];
	h=((h+3)/4)*4;

	ll ans=1;
	//4分割
	rep(z,4){
		//模様の取り出し、向き合わせ(下２つのグループは上下反転)&(偶数列は上下反転)
		vvl moyou(w,vl(h/4));
		rep(i,w){
			rep(j,h/4){
				if(s[j*4+(z+(i%2)*2)%4][i]=='.')moyou[i][j]=1;
				else moyou[i][j]=0;
			}
			//この時反転
			if((i%2==1&&z<=1)||(i%2==0&&z>=2))reverse(moyou[i].begin(),moyou[i].end());
		}

		//上下交互に＆を取ったビット列を生成後、3^N DP
		vvl dp(w+1,vl(1<<(h/4),0));
		
		dp[0][0]=1;

		//渡すDP
		rep(i,w){
			rep(j,1<<(h/4)){
				//dp[i][j]が0ならcontinue
				if(dp[i][j]==0)continue;

				//tmpはjのビットを配列として反転したもの
				ll tmp=0;
				rep(k,h/4)if((1<<k)&j)tmp+=1<<((h/4-1)-k);

				//bitは今、遷移先として、bitを1にできるものを全て1にした物。
				ll bit=0;
				if(tmp%2==0&&moyou[i][0]==1)bit++;
				loop(k,1,(h/4-1))if(((1<<k)&tmp)==0&&((1<<(k-1))&tmp)==0&&moyou[i][k]==1)bit+=1<<k;

				//bitの部分列全てに、dp[i][j]を足す。3^N DP
				ll b=bit;
				while(1){
					dp[i+1][b]+=dp[i][j];
					dp[i+1][b]%=mod;
					if(b==0)break;
					b=((b-1)&bit);
				}
			}
		}
		ll mul=0;
		rep(j,1<<(h/4))mul+=dp[w][j];
		mul%=mod;
		ans*=mul,ans%=mod;

		//vvdbg(dp);
		//cout<<endl;
	}
	cout<<ans<<endl;
	return true;
}

int main(){
	while(solve());
	return 0;
}