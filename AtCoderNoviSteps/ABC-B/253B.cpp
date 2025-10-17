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
	vector<string> s(h);
	rep(i,h)cin>>s[i];

	ll px,py,qx,qy;

	rep(i,h)rep(j,w){
		if(s[i][j]=='o')px=i,py=j;
	}
	rep(i,h)rep(j,w){
		if(s[i][j]=='o'){
			qx=i,qy=j;
			cout<<abs(px-qx)+abs(py-qy)<<endl;
			return 0;
		}
	}
	

	return 0;
}