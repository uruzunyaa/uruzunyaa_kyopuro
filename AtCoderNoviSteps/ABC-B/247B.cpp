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
	map<string,ll> u;
	vector<string> s(n);
	vector<string> t(n);
	rep(i,n){
		cin>>s[i]>>t[i];
		u[s[i]]++;
		if(s[i]!=t[i])u[t[i]]++;

	}

	rep(i,n){
		if(u[s[i]]!=1&&u[t[i]]!=1){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}