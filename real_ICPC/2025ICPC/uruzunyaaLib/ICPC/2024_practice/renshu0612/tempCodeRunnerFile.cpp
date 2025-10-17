#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353LL

//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

//オイラーのトーシェント関数。N以下のNと互いに素な物の数を返す。
ll euler(ll n){
	unordered_map<ll,ll> factors;
	ll tmp=n;
	while (tmp % 2 == 0) {
		factors[2]++;
		tmp /= 2;
	}
	for (ll i=3; i*i<=tmp;i+=2) {
		while (tmp%i == 0) {
			factors[i]++;
			tmp/= i;
		}
	}
	if (tmp > 2)factors[tmp]++;
	ll ans=1;
	for(const auto & val:factors){
		ans*=power(val.first,val.second-1)*(val.first-1);
	}
	return ans;
}


map<ll,ll> makeMapPrime(ll n){
	map<ll,ll> factors;
	while (n % 2 == 0) {
		factors[2]++;
		n /= 2;
	}
	for (ll i=3; i*i<=n;i+=2) {
		while (n%i == 0) {
			factors[i]++;
			n /= i;
		}
	}
	if (n > 2) {
		factors[n]++;
	}
	return factors;
}


ll solve(){
	ll m,a;
	cin>>m>>a;
	if(m==0)return 1;
	ll g=gcd(m,a);
	map<ll,ll>p=makeMapPrime(m/g);

	ll ans=gcd(m/g,g);
	ll tmp=1;
	range(val,p){
		while(m%val.first==0)m/=val.first;
	}
	//オイラー関数で１回の周期内の個数を求めている。
	ans*=euler(m);

	cout<<ans<<endl;

	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}