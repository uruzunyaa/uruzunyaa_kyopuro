//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
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


ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

//nCr % mod を O(max(n)) で求める(power_mod前提条件)
vl fact={1};
vl factinv={1};
ll ncrmd(ll n,ll r){
	while(fact.size()<=n){
		ll i=fact.size();
		fact.push_back((fact[i-1]*i)%mod);
		factinv.push_back(power_mod(fact[i],mod-2));
	}
	ll ans=fact[n];
	ans*=factinv[r];
	ans%=mod;
	ans*=factinv[n-r];
	ans%=mod;
	return ans;
}


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

void solve(){
	ll n;
	cin>>n;
	ll sum=0;
	vl a(n);
	rep(i,n)cin>>a[i],sum+=a[i];

	if(sum!=n){
		cout<<0<<endl;
		return;
	}

	ll start=n/2;
	ll cnt=n%2;
	cnt-=2;
	ll ans=1;

	rrep(i,start+1){
		cnt+=2;
		if(cnt<a[i]){
			//上に集まりすぎ
			ans=0;
			break;
		}
		ans*=ncrmd(cnt,a[i]);
		cnt-=a[i];
		ans%=mod;
	}

	if(cnt!=0)ans=0;

	cout<<ans<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();	
	return 0;
}
