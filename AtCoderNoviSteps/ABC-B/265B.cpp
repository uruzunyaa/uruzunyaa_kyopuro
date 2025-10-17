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
	ll n,m,t;
	cin>>n>>m>>t;
	vl a(n-1);
	rep(i,n-1)cin>>a[i];
	ll gps=0;
	rep(i,m){
		ll x,y;
		cin>>x>>y,x--;
		while(1){
			t-=a[gps];
			gps+=1;
			if(t<=0){
				cout<<"No"<<endl;
				return 0;
			}
			if(gps==x)break;
		}
		t+=y;
	}
	while(1){
		t-=a[gps];
		gps+=1;
		if(t<=0){
			cout<<"No"<<endl;
			return 0;
		}
		if(gps==n-1)break;
	}
	cout<<"Yes"<<endl;
	return 0;
}