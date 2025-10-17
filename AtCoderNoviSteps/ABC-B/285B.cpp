#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n;
	string s;
	cin>>n>>s;
	loop(i,1,n-1){
		ll ans=0;
		loop(j,0,n-i-1){
			if(s[j]!=s[j+i])ans++;
			else break;
		}
		cout<<ans<<endl;
	}
	return 0;
}