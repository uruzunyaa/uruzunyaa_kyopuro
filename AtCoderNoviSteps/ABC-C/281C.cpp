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
	ll n,t;
	cin>>n>>t;
	vl a(n);
	ll sum=0;
	rep(i,n)cin>>a[i],sum+=a[i];

	t%=sum;

	rep(i,n){
		if(t<a[i]){
			cout<<i+1<<" "<<t<<endl;
			return 0;
		}else t-=a[i];
	}
	return 0;
}