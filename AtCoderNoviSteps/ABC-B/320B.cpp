#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
int main(){
	string s;
	cin>>s;
	ll n=s.size();
	ll ans=1;
	rep(i,n){
		rep(j,i+1){
			bool f=true;
			rep(k,i-j+1){
				if(s[j+k]!=s[i-k])f=false;
			}
			if(f)ans=max(ans,i-j+1);
		}
	}
	cout<<ans<<endl;
	return 0;
}