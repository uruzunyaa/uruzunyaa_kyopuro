#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n,m;
	cin>>n>>m;
	vector<string> s(n);
	rep(i,n)cin>>s[i];
	ll ans=0;
	rep(i,n){
		rep(j,i){
			bool f=true;
			rep(k,m){
				if(s[i][k]=='x'&&s[j][k]=='x')f=false;
			}
			if(f)ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}