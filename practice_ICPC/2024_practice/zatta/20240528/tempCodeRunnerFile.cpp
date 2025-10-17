#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
ll solve(){
	ll n;
	cin>>n;
	if(n==0)return 1;
	ll a=0;
	for(ll i=1;i*i*i<=n;i++){
		if(n%i==0)a=i;
	}
	n/=a;
	ll b=0;
	for(ll i=1;i*i<=n;i++){
		if(n%i==0)b=i;
	}
	n/=b;
	if(b==1){
		for(ll i=1;i*i<=a;i++){
			if(a%i==0)b=i;
		}
		a/=b;
	}
	cout<<a+b+n<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}