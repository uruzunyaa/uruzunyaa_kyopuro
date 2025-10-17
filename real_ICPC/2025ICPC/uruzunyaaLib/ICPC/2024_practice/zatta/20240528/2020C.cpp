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
	vl y;
	for(ll i=1;i*i<=n;i++){
		if(n%i==0)y.push_back(i),y.push_back(n/i);
	}
	sort(y.begin(),y.end());

	ll mn=inf;
	rep(i,y.size()){
		rep(j,i+1){
			if(y[i]*y[j]>n)break;
			if(n%(y[i]*y[j])!=0)continue;
			mn=min(y[i]+y[j]+(n/y[i]/y[j]),mn);
		}
	}

	cout<<mn<<endl;

	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}