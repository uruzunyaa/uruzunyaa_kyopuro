#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	vector<string> s(8);
	rep(i,8)cin>>s[i];

	rep(i,8)rep(j,8){
		if(s[i][j]=='*'){
			char ans=j+'a';
			cout<<ans<<8-i<<endl;
			return 0;
		}
	}
	return 0;
}