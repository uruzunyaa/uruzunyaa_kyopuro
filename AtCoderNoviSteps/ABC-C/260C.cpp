#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll n,x,y;
	cin>>n>>x>>y;
	vl r(n+1,0),b(n+1,0);
	r[n]++;
	for(ll i=n;i>=2;i--){
		r[i-1]+=r[i];
		b[i]+=x*r[i];
		r[i-1]+=b[i];
		b[i-1]+=b[i]*y;
	}
	cout<<b[1]<<endl;
	return 0;
}
