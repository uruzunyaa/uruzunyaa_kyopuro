#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define mod 1000000007LL
#define inf 4000000000000000000LL
//エラトステネスの篩方式で素因数分解機能を付けた

vl eprime;
//maxaまでの全ての数について、最小の素因数を求め,eprimeに入れる
void make_eratosthenes_prime(ll maxa){
	eprime=vl(maxa+1);
	loop(i,2,maxa){
		if(eprime[i]==0){
			eprime[i]=i;
			for(ll j=i*i;j<=maxa;j+=i){
				if(eprime[j]==0)eprime[j]=i;
			}
		}
	}
}
//make_eratosthenes_primeで作られている前提で、素因数分解をする。
vector<pair<ll,ll>> eratosthenes_prime_fact(ll n){
	vector<pair<ll,ll>> ans;
	while(n!=1){
		if(ans.size()==0||ans.back().first!=eprime[n]){
			ans.push_back({eprime[n],1});
		}else{
			ans.back().second++;
		}
		n/=eprime[n];
	}
	return ans;
}


// nのk乗をmodで割った余りを計算(modはdefineで定義想定)
ll power_mod(ll n, ll k){
	n%=mod;
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return ans;
}

//メイン
int main(){
	ll n;
	cin>>n;
	make_eratosthenes_prime(1000000);
	vl mxs(1000001,0);
	ll mn=inf;
	rep(i,n){
		ll a;
		cin>>a;
		mn=min(a,mn);
		vector<pair<ll,ll>> tmp=eratosthenes_prime_fact(a);
		for(auto val:tmp){
			mxs[val.first]=max(mxs[val.first],val.second);
		}
	}
	ll ans=power_mod(mn,mod-2);
	loop(i,1,1000000){
		ans*=power_mod(i,mxs[i]);
		ans%=mod;
	}
	cout<<ans<<endl;

	
	return 0;
}
