#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<n;i++)
#define rrep(i,n) for(ll i=n-1;i>=0;i--)

#define vl vector<ll> 
#define inf 1000000000000000000LL
int main(){
	ll n,l;
	cin>>n>>l;
	vl b(n),w(n);
	rep(i,n)cin>>b[i];
	ll sum=0;
	rep(i,n)cin>>w[i],sum+=w[i];
	
	ll k,p;
	cin>>k>>p;
	k--;

	if(p+w[k]>l){
		cout<<"NO"<<endl;
		return 0;
	}

	ll yoryoku=l-sum;
	ll cnt=0;

	rep(i,n)if(w[i]>yoryoku&&i!=k)cnt++;

	ll left=p;
	ll right=l-(p+w[k]);
	
	
	rep(i,n){
		if(w[k]>yoryoku&&i==k)break;
		if(w[i]<=yoryoku)continue;
		left-=w[i];
		if(left<0)break;
		else cnt--;
	}
	rrep(i,n){
		if(w[k]>yoryoku&&i==k)break;
		if(w[i]<=yoryoku)continue;
		right-=w[i];
		if(right<0)break;
		else cnt--;
	}

	if(cnt<=0)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}