// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#ifdef DEBUG
#include "cpp-dump/dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#endif
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
#define mod 998244353

ll solve() {
	ll n;
	cin>>n;
	
	if (n==0) return 1;

	vl k(n);
	rep(i,n){
		cin>>k[i];
	}
	string s;
	cin>>s;

	vl c(s.size());
	rep(i,s.size()){
		if('a'<=s[i]&&s[i]<='z'){
			c[i]=s[i]-'a';
		}else{
			c[i]=s[i]-'A'+26;
		}
		c[i]-=k[i%n];
		if(c[i]<0)c[i]+=52;
		
		if(c[i]<26){
			char ans=c[i]+'a';
			cout<<ans;
		}else{
			char ans=c[i]+'A'-26;
			cout<<ans;
		}
	}

	cout<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}
