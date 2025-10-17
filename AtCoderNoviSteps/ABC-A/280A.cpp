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
	ll h,w;
	cin>>h>>w;
	vector<string>s(h);
	rep(i,h)cin>>s[i];

	ll ans=0;

	rep(i,h)rep(j,w){
		if(s[i][j]=='#')ans++;
	}
	cout<<ans<<endl;
	return 0;
}