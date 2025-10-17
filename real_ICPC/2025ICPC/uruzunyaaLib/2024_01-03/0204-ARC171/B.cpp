#include<iostream>//入出力
#include<algorithm>//アルゴリズム
#include<vector>//配列
#include<string>//文字列
#include<set>//セット
#include<unordered_set>//ハッシュセット
#include<map>//木構造マップ
#include<unordered_map>//ハッシュマップ
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
#define inf 4000000000000000000
#define mod 998244353
//#define mod 1000000007

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n){
		cin>>a[i],a[i]--;
		if(a[i]<i){
			cout<<0<<endl;
			return 0;
		}
	}

	//コーナーケース対応
	//2 3 3のようなケースをはじく
	rep(i,n){
		if(a[a[i]]!=a[i]){
			cout<<0<<endl;
			return 0;
		}
	}
	//使われる場所が確定した数字の集合
	set<ll> k;
	//kの補集合
	set<ll> rk;
	rep(i,n)rk.insert(i);
	vl s;
	rep(i,n){
		if(a[i]!=i){
			if(k.count(a[i])==0){
				k.insert(a[i]);
				rk.erase(a[i]);
			}else{
				k.insert(i);
				rk.erase(i);
			}
		}else{
			s.push_back(i);
		}
	}
	ll cnt=1;
	ll t=0;
	ll ans=1;
	for(auto it = rk.rbegin();it!=rk.rend();it++){
		while(*it <= s[s.size()-cnt-1] && s.size()!=cnt)cnt++;
		
		ans*=cnt-t;
		ans%=mod;

		t++;
		//cout<<*it<<endl;
	}

	cout<<ans<<endl;

	//range(v,rk)cout<<v<<endl;
	return 0;
}
