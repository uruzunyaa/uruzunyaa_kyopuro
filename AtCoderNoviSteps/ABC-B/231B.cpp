#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353
int main(){
	ll n;
	cin>>n;
	vector<string> s(n);
	map<string,ll> a;
	ll mx=0;
	rep(i,n){
		cin>>s[i];
		a[s[i]]++;
		mx=max(mx,a[s[i]]);
	}

	for(const auto &val:a){
		if(val.second==mx)cout<<val.first<<endl;
	}
	
	return 0;
}