#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<n;i++)
#define vl vector<ll> 
#define inf 1000000000000000000LL
int main(){
	ll n,x;
	cin>>n>>x;
	vl a(n),b(n);
	rep(i,n)cin>>a[i];
	rep(i,n)cin>>b[i];
	
	ll mx=inf;
	ll mn=0;

	while(mn!=mx){
		ll mid=mn+mx+1;
		mid/=2;
		ll num=mid/n;
		ll ind=mid%n;

		ll cnt=x;
		//番号がindより前はnum以下の数字なら加算indより後はnum未満なら加算

		rep(i,n){
			ll tmp=num-a[i];
			if(i>ind)tmp--;
			if(tmp<0)continue;
			cnt-=tmp/b[i];
			cnt--;
		}
		if(cnt<0)mx=mid-1;
		else mn=mid;
	}

	ll num=mx/n;
	ll ind=mx%n;

	rep(i,n){
		ll tmp=num-a[i];
		if(i>ind)tmp--;
		if(tmp<0)continue;
		a[i]+=(tmp/b[i]+1)*b[i];
	}

	rep(i,n)cout<<a[i]<<" ";
	cout<<endl;
}