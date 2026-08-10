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


ll power_mod(ll n, ll k){
	n%=mod;
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

//nCr % mod を O(max(n)) で求める(power_mod前提条件)
//注意:先に階乗逆元等を求める関数を動かさないと
//O(Max(n log n))になる。
vl fact={1};
vl factinv={1};
void make_fact_and_factinv(ll n){
	fact=vl(n+1);
	factinv=vl(n+1);
	fact[0]=1;
	loop(i,1,n){
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
	}
	factinv[n]=power_mod(fact[n],mod-2);
	rrep(i,n){
		factinv[i]=factinv[i+1]*(i+1);
		factinv[i]%=mod;
	}
}
ll ncrmd(ll n,ll r){
	if(r<0||n<r)return 0;
	while(fact.size()<=n){
		ll i=fact.size();
		fact.push_back((fact[i-1]*i)%mod);
		factinv.push_back(power_mod(fact[i],mod-2));
	}
	ll ans=fact[n]*factinv[r];
	ans%=mod;
	ans*=factinv[n-r];
	ans%=mod;
	return ans;
}

void solve(){
	ll n,k;
	cin>>n>>k;
	vl a(n);
	rep(i,n)cin>>a[i];
	ll m=0;
	rloop(i,n-1,n-k){
		m|=a[i];
	}
	ll ans=0;
	rrep(i,n){
		if(k==0)break;
		//これを選べば自由,選ばない事も出来る
		if((m&a[i])==m){
			//選んだ場合
			ans+=ncrmd(i,k-1);
			ans%=mod;
		}else{
			//強制で選ぶ
			rep(b,60){
				if(((1LL<<b)&m)&&((1LL<<b)&a[i])){
					m-=(1LL<<b);
				}
			}
			k--;
		}
	}
	cout<<ans<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	make_fact_and_factinv(300000);
	rep(i,t){
		solve();
	}
	return 0;
}
