#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define inf 4000000000000000000
#define mod 998244353
//#define mod 1000000007

int main(){
	ll n,q;
	cin>>n>>q;
	vector<map<ll,ll>> c(n);

	//各箱の初期状態を連想配列形式で持つ
	rep(i,n){
		ll temp;
		cin>>temp;
		c[i][temp]=1;
	}

	rep(z,q){
		//query読み込み
		ll a,b;
		cin>>a>>b,a--,b--;

		//結合処理前に、小さい方を大きい方に移動する形へ入れ替え
		if(c[b].size()<c[a].size())swap(c[a],c[b]);
		
		//結合のためにAをBにコピー
		range(val,c[a]) c[b][val.first]=val.second;

		//コピーの終わったAを空に
		c[a].clear();

		//出力
		cout<<c[b].size()<<endl;
	}
	return 0;
}