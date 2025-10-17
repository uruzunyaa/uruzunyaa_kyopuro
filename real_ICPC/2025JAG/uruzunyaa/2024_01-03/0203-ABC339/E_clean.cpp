#include<bits/stdc++.h>
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
	ll n,d;
	cin>>n>>d;
	vl a(n);
	rep(i,n)cin>>a[i];

	map<ll,ll> c;
	c[-d-d]=0;
	c[500000+d+d]=0;

	rep(i,n){
		//自分がいる区間の値を取得し、1増やす
		auto it=c.upper_bound(a[i]);
		it--;
		ll num=(it->second)+1;

		//区間の端を追加
		auto mx=c.upper_bound(a[i]+d+1);
		mx--;
		c[a[i]+d+1]=mx->second;

		//区間の下限を指す区間を取得
		auto mn2=c.upper_bound(a[i]-d);
		mn2--;
		
		//最善が更新されているなら更新
		if((mn2->second)<num){
			c[a[i]-d]=num;
		}

		//再度要素の最小部分の区間新たに取得
		auto mn=c.upper_bound(a[i]-d);
		mn--;
		//区間の上書き
		while(1){
			//次ポインタの取得
			auto cp=mn;
			cp++;
			//対象範囲を出たらbreak
			if((cp->first)>a[i]+d)break;
			//最高値更新かをみる
			if((cp->second)<=num){
				//同じ数字の区間になってるなら、区間の削減
				//異なる数字なら区間の最初に設定
				if((mn->second)==num){
					c.erase(cp);
				}else{
					cp->second=num;
					mn++;
				}
				
			}else {
				//更新すべき場所じゃなければポインタを進める
				mn++;
			}
		}
	}
	
	ll ans=-inf;
	range(val,c){
		ans=max(val.second,ans); 
	}
	cout<<ans<<endl;

	return 0;
}
