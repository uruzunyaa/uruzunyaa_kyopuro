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

vl three={1,3,9,27,81,243,729,2187,6561,19683};
vl a(9);
vl dp(three[9],-1);
//その手番で先手が勝てるなら1、負けなら2を返す
ll fdp(ll bit){
	if(dp[bit]!=-1)return dp[bit];
	ll bito=bit;
	vl b;
	ll zero=0;
	rep(i,9){
		if(bit%3==0)zero++;
		b.push_back(bit%3),bit/=3;
	}
	//揃っていないかチェック
	if(b[0]==b[1]&&b[1]==b[2]&&b[2]!=0)return b[0];
	if(b[3]==b[4]&&b[4]==b[5]&&b[5]!=0)return b[3];
	if(b[6]==b[7]&&b[7]==b[8]&&b[8]!=0)return b[6];
	if(b[0]==b[3]&&b[3]==b[6]&&b[6]!=0)return b[0];
	if(b[1]==b[4]&&b[4]==b[7]&&b[7]!=0)return b[1];
	if(b[2]==b[5]&&b[5]==b[8]&&b[8]!=0)return b[2];
	if(b[0]==b[4]&&b[4]==b[8]&&b[8]!=0)return b[0];
	if(b[2]==b[4]&&b[4]==b[6]&&b[6]!=0)return b[2];

	//全員の操作が終了した場合
	if(zero==0){
		//揃ってない時、スコアを判定
		ll sct=0,sca=0;
		rep(i,9){
			if(b[i]==1)sct+=a[i];
			else sca+=a[i];
		}
		if(sct>sca)return 1;
		else return 2;
	}else if(zero%2==1){
		//高橋のターン
		rep(i,9){
			if(b[i]!=0)continue;
			dp[bito+three[i]]=fdp(bito+three[i]);
			if(dp[bito+three[i]]==1)return 1;
		}
		return 2;
	}else{
		//青木のターン
		rep(i,9){
			if(b[i]!=0)continue;
			dp[bito+three[i]*2]=fdp(bito+three[i]*2);
			if(dp[bito+three[i]*2]==2)return 2;
		}
		return 1;
	}
}
//メイン
int main(){
	rep(i,9)cin>>a[i];

	if(fdp(0)==1)cout<<"Takahashi"<<endl;
	else cout<<"Aoki"<<endl;

	return 0;
}
