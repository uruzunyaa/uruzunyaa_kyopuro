#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define rep(i,n)for(ll i=0;i<n;i++)
ll power(ll a,ll b){
	ll ans=1;
	rep(i,b)ans*=a;
	return ans;
}
int main(){
	ll n;
	cin>>n;
	vl f(n);
	rep(i,n)cin>>f[i],f[i]--;
	vvl ansl;
	rep(i,power(n,n)){
		vl g;
		ll tmp=i;
		rep(i,n){
			g.push_back(tmp%n);
			tmp/=n;
		}
		bool b=true;
		rep(i,n){
			if(g[f[i]]!=f[g[i]])b=false;
		}
		if(b){
			vl ttmp;
			rep(i,n)ttmp.push_back(g[i]);
			ansl.push_back(ttmp);
		}
	}
	sort(ansl.begin(),ansl.end());
	rep(i,ansl.size()){
		rep(j,n)cout<<ansl[i][j]+1<<" ";
		cout<<endl;
	}
}