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
#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

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

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	if(n==1){
		cout<<m*2+1<<endl;
		return 0;
	}

	make_fact_and_factinv(20000000);

	//奇数項での増加量と偶数項での増加量の数え上げを求める
	vl odd={1},even={1};

	//i増加する
	loop(i,1,m){
		//n/2項に割り振る
		odd.push_back(ncrmd(n/2-1+i,i));
	}

	if(n==2){
		ll ans=0;
		loop(i,0,m){
			ans+=odd[i]*(m*2+1-i);
			ans%=mod;
		}
		cout<<ans<<endl;
		return 0;
	}

	loop(i,1,m){
		//(n-1)/2項に割り振る
		even.push_back(ncrmd((n-1)/2-1+i,i));
	}

	ll evensum=0;
	ll minus=0;
	loop(i,0,m){
		minus+=even[i];
		minus%=mod;
		evensum+=(2*m+1-i)*even[i];
		evensum%=mod;
	}
	ll ans=0;
	loop(i,0,m){
		ans+=odd[i]*evensum;
		ans%=mod;
		evensum+=mod-minus;
		evensum%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
