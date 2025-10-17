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
	ll r,c;
	cin>>r>>c;
	ll mx = max(abs(r-8),abs(c-8));

	if(mx%2==0)cout<<"white"<<endl;
	else cout<<"black"<<endl;

	return 0;
}