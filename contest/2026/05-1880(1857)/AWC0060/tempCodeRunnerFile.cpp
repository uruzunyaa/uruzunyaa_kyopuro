//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k,ll m){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%m;
		n=n*n%m;
		k >>= 1;
	}
	return result;
}



//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};


ll m;
//functional_graphをダブリングする構造
//get(t,k)で頂点tからk回移動後が取得可能
struct Doubling {
	ll n;
	vector<vector<pair<ll,ll>>> dp;
	//functional_graphを与える
	Doubling(vector<pair<ll,ll>> a) {
		n=a.size();
		dp.push_back(a);
		loop(i,1,60){
			vector<pair<ll,ll>> nx(n);
			rep(j,n){
				nx[j]={dp.back()[dp.back()[j].first].first,dp.back()[j].second*power_mod(10,1LL<<(i-1),m)+dp.back()[dp.back()[j].first].second};
				nx[j].second%=m;
			}
			dp.push_back(nx);
			vpdbg(nx);
		}
	}
	
	// 頂点tからk回移動した時の頂点を返す(2^60を超える場合は注意)
	ll get(ll t, ll k){
		ll i=0;
		ll ans=0;
		while (k > 0){
			if ((k&1) ==1){
				ans=ans*power_mod(10,1LL<<i,m)+dp[i][t].second;
				ans%=m;
				t=dp[i][t].first;
			}
			i++;
			k >>= 1;
		}
		return ans;
	}
};



//メイン
int main(){
	ll n,q;
	cin>>n>>q>>m;
	vector<pair<ll,ll>> pd;
	rep(i,n){
		ll dd,pp;
		cin>>dd>>pp;
		pp--;
		pd.push_back({pp,dd});
	}
	Doubling db(pd);
	while(q--){
		ll s,k;
		cin>>s>>k;
		s--;
		cout<<db.get(s,k)<<endl;
	}
	return 0;
}
