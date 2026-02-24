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

//メイン
int main(){
	ll q;
	cin>>q;
	vector<pair<ll,ll>>b;
	//b[i].first=これまでの要素数。
	//b[i].second=色
	b.push_back(make_pair(0,0));
	rep(z,q){
		ll s;
		cin>>s;
		if(s==1){
			ll x,c;
			cin>>x>>c;
			b.push_back(make_pair(b.rbegin()->first+x,c));
			//cout<<b.rbegin()->first<<endl;
		}else if(s==2){
			ll x;
			cin>>x;
			//底からx番目まで残る
			x=b.rbegin()->first-x;
			auto it=lower_bound(b.begin(),b.end(),make_pair(x,-inf));
			it->first=x;
			if(it!=b.end())b.erase(it+1,b.end());
		}else{
			ll x;
			cin>>x;
			x=b.rbegin()->first+1-x;
			ll ans=lower_bound(b.begin(),b.end(),make_pair(x,-inf))->second;
			cout<<ans<<endl;
		}
	}
}
