#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n,q;
	cin>>n>>q;
	vl c(n,0);
	rep(z,q){
		ll t,x;
		cin>>t>>x,x--;
		if(t<=2)c[x]+=t;
		else {
			if(c[x]>=2)cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	return 0;
}