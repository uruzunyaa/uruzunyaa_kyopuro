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
int main(){
	ll n,m;
	cin>>n>>m;
	vl a(n),b(m),c(n+m);
	
	rep(i,n)cin>>a[i],c[i]=a[i];
	rep(i,m)cin>>b[i],c[n+i]=b[i];
	
	sort(c.begin(),c.end());

	ll ans=0;
	rep(i,n+m){
		if(a[ans]==c[i]){
			ans++;
			cout<<i+1<<" ";
		}
	}
	cout<<endl;
	ans=0;
	rep(i,n+m){
		if(b[ans]==c[i]){
			ans++;
			cout<<i+1<<" ";
		}
	}
	cout<<endl;
	return 0;
}