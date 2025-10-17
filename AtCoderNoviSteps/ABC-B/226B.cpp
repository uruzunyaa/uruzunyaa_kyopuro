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
	map<vl,ll> a;
	
	rep(i,n){
		ll l;
		cin>>l;
		vl aa(l);
		rep(j,l)cin>>aa[j];
		a[aa]++;
	}
	cout<<a.size()<<endl;
	return 0;
}