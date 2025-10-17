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
	ll n,k;
	cin>>n>>k;
	vl a(n);
	vector<bool> t(k+1,false);

	rep(i,n)cin>>a[i],t[min(a[i],k)]=true;

	rep(i,k)if(!t[i]){
		cout<<i<<endl;
		return 0;
	}
	cout<<k<<endl;

	return 0;
}