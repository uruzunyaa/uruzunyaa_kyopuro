#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
int main(){
	ll n;
	cin>>n;
	vector<ll> a(n);
	rep(i,n)cin>>a[i];

	ll q;
	cin>>q;
	rep(i,q){
		ll m;
		cin>>m;
		if(m==1){
			ll k,x;
			cin>>k>>x,k--;
			a[k]=x;
		}else{	
			ll k;
			cin>>k,k--;
			cout<<a[k]<<endl;
		}
	}
	return 0;
}