//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// order_of_key : x 未満である要素数を取得する
// find_by_order : 0-indexed で k 番目に小さい値を指すイテレータを取得する
// eraseの際、必ずイテレーターで消す事。

//メイン
int main(){
	ll n,x,y;
	cin>>n>>x>>y;
	vector<pair<ll,ll>> ab(n);
	rep(i,n)cin>>ab[i].first>>ab[i].second;
	sort(ab.begin(),ab.end());

	ordered_set<pair<ll,ll>> aok;
	ll r=n-1;
	ll ans=0;
	rep(l,n-1){
		//OKを追加
		while(r>l&&x-ab[l].first<=ab[r].first){
			aok.insert({ab[r].second,r});
			r--;
		}

		//答えを求める
		ll tmp=aok.order_of_key({y-ab[l].second,-inf}); 
		ans+=aok.size()-tmp;

		//rとlが重なってたら、除去
		if(r==l){
			r++;
			aok.erase({ab[r].second,r});
		}
	}
	cout<<ans<<endl;

	return 0;
}
