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
	ll x,k;
	cin>>x>>k;
	vl t(k+1);
	t[0]=1;
	loop(i,1,k)t[i]=t[i-1]*10;
	rep(i,k){
		if(x%t[i+1]<5*t[i])x-=x%t[i+1];
		else x+=t[i+1]-x%t[i+1];
	}
	cout<<x<<endl;
	return 0;
}