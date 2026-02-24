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

//メイン
int main(){
	vl two(51);
	two[0]=1;
	rep(i,50)two[i+1]=two[i]*2;
	vl five(51);
	five[0]=1;
	rep(i,50)five[i+1]=five[i]*5;
	
	loop(x,0,50){
		vl fx(10,0);
		rep(i,10){
			ll tmp=five[x]*two[i];
			string st=to_string(tmp);
			rep(j,st.size())fx[i]+=st[j]-'0';
		}
		bool f=true;
		rep(i,3){
			if(fx[i]<=fx[i+1])f=false;
		}
		if(f)cout<<five[x]<<endl;
	}
	return 0;
}
