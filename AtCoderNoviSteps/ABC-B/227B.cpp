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
	vl s(n);
	rep(i,n)cin>>s[i];
	unordered_set<ll>a;
	loop(i,1,1000){
		loop(j,1,1000){
			a.insert(4*i*j+3*i+3*j);
		}
	}
	ll ans=n;
	rep(i,n){
		if(a.count(s[i]))ans--;
	}
	cout<<ans<<endl;
	return 0;
}