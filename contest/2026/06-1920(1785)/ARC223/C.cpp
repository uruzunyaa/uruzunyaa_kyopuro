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
	if(n<r)return 0;
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

//転倒数を求める
ll inversion_number(vl &v) {
	int n = v.size();
	if (n == 1) return 0;
	vl v1(v.begin(), v.begin() + n / 2);
	vl v2(v.begin() + n / 2, v.end());
	ll res = inversion_number(v1) + inversion_number(v2);
	int p = 0, q = 0;
	for (int i = 0; i < n; i++) {
		if (q == v2.size() || (p < v1.size() && v1[p] <= v2[q])) {
			v[i] = v1[p++];
		}else {
			v[i] = v2[q++];
			res += v1.size() - p;
		}
    }
    return res;
}


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

void solve(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	sort(a.begin(),a.end());
	rep(i,n)a[i]%=n;

	vl bk(n,0);
	loop(i,2,n-1){
		if(n%i==0){
			cout<<0<<endl;
			return;
		}
	}
	rep(i,n){
		bk[a[i]]++;
		if(bk[a[i]]==2){
			cout<<0<<endl;
			return;
		}
	}

	ll ans=1;
	ll seki=1;
	loop(i,1,n-1){
		seki*=i;
		seki%=n;
		ans*=seki;
		ans%=n;
	}

	ll tmp=inversion_number(a);
	tmp%=2;
	if(tmp==1)ans=n-ans;
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
