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
	ll n,k;
	cin>>n>>k;
	vl a(n);
	vl b(k);
	rep(i,n)cin>>a[i];
	rep(i,k)cin>>b[i],b[i]--;
	string ans="No";
	ll mx=*max_element(a.begin(),a.end());
	rep(i,k){
		if(a[b[i]]==mx)ans="Yes";
	}

	cout<<ans<<endl;
	return 0;
}