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
	ll h,w;
	cin>>h>>w;
	ll n=min(h,w);
	vl ans(n+1,0);

	vector<string> c(h);
	rep(i,h)cin>>c[i];

	loop(i,1,h-2)loop(j,1,w-2){
		if(c[i][j]!='#')continue;
		loop(k,1,n){
			if(i+k>=h||j+k>=w||i-k<0||j-k<0||c[i+k][j+k]=='.'||c[i+k][j-k]=='.'||c[i-k][j+k]=='.'||c[i-k][j-k]=='.'){
				ans[k-1]++;
				break;
			}
		}
	}
	loop(i,1,n)cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}