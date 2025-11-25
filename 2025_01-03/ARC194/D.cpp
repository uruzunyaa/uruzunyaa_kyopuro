#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define mod 998244353LL

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

ll i=1;
string s;
ll dfs(){
	ll ans=1;
	map<string,ll> cnt;
	vector<string> news;
	ll indexs=i;
	while(s[i]!=')'){
		ll mae=i;
		i++;
		ans*=dfs();
		ans%=mod;
		news.push_back(s.substr(mae,i-mae));
		cnt[s.substr(mae,i-mae)]++;
	}

	sort(news.begin(),news.end());
	rep(j,news.size()){
		rep(k,news[j].size()){
			s[indexs]=news[j][k];
			indexs++;
		}
	}

	ll sum=0;
	for(const auto &val:cnt){
		sum+=val.second;
		ans*=ncrmd(sum,val.second);
		ans%=mod;
	}
	i++;
	return ans;
}
//メイン
int main(){
	ll n;
	cin>>n;
	cin>>s;
	s.insert(s.begin(),'(');
	s.insert(s.end(),')');
	
	cout<<dfs()<<endl;
	
	return 0;
}
