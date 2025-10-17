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
	ll n;
	string s;
	cin>>n>>s;
	ll cnt=0;
	ll mx=-1;
	rep(i,n){
		if(s[i]=='o')cnt++;
		else cnt=0;
		mx=max(mx,cnt);
	}
	if(mx==n||mx==0)mx=-1;
	cout<<mx<<endl;
	return 0;
}