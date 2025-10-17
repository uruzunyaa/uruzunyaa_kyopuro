#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll r,c;
	cin>>r>>c;
	vector<string> b(r);
	rep(i,r)cin>>b[i];

	vector<string>ans(r,string(c,'#'));
	rep(i,r)rep(j,c)ans[i][j]=b[i][j];

	rep(i,r)rep(j,c){
		if('0'<=b[i][j]&&b[i][j]<='9'){
			ll tmp=b[i][j]-'0';
			rep(k,r)rep(l,c){
				if(abs(i-k)+abs(j-l)<=tmp)ans[k][l]='.';
			}
		}
	}
	rep(i,r)cout<<ans[i]<<endl;
	return 0;
}