#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

//メイン
int main(){
	ll n;
	cin>>n;
	vl p(n),q(n),trp(n+1),trq(n+1);
	rep(i,n)cin>>p[i],trp[p[i]-1]=i+1;
	rep(i,n)cin>>q[i],trq[q[i]-1]=i+1;
	vector<string> ans(n,string(n,'0'));
	
	rep(i,n)rep(j,n){
		if(trp[i]+trq[j]>n)ans[i][j]='1';
	}
	rep(i,n)cout<<ans[i]<<endl;
	return 0;
}
