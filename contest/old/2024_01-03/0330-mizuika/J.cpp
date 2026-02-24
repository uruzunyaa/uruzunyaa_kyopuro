#include<iostream>//入出力
#include<algorithm>//アルゴリズム
#include<vector>//配列
#include<string>//文字列
#include<functional>//関数型変数
#include<set>//セット
#include<unordered_set>//ハッシュセット
#include<map>//木構造マップ
#include<unordered_map>//ハッシュマップ
#include<queue>//キュー、優先度付きキュー
#include<deque>//スタックとキュー
#include<iomanip>//出力形式調整
#include<tuple>//pairの複数型
#include<cmath>//数学。ルートとか
#include<cctype>//大文字小文字のチェックなど
#include<fstream>//ファイル入出力
#include<random>//乱数
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
#define mod 998244353
//#define mod 1000000007

//dp[i][j]=i個目の要素がjである時のそれ以降の通り。
vvl dp(5001,vl(5001,-1));
ll n,k;

//s個目の文字がmである時、それ以降の通り。
//最初が上に上がると決め打ちする。
ll sub(ll s,ll m){
	if(dp[s][m]!=-1)return dp[s][m];
	if(s==n)return 1;

	dp[s][m]=0;
	if(s%2==1){
		//次の数字は上に上がる
		loop(i,m+1,k){
			dp[s][m]+=sub(s+1,i);
			dp[s][m]%=mod;
		}
	}else{
		//次の数字は下に下がる
		loop(i,1,m-1){
			dp[s][m]+=sub(s+1,i);
			dp[s][m]%=mod;
		}
	}
	return dp[s][m];
}

//メイン
int main(){
	if(n==1){
		cout<<1<<endl;
		return 0;
	}
	cin>>n>>k;
	ll ans=0;
	loop(i,1,n){
		ans+=sub(1,i);
		ans%=mod;
	}

	ans*=2;
	ans%=mod;
	cout<<ans<<endl;
	return 0;
}
