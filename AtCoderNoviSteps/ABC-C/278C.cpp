#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	set<pair<ll,ll>> s;
	rep(i,q){
		ll t,a,b;
		cin>>t>>a>>b;
		if(t==1){
			s.insert({a,b});
		}else if(t==2){
			s.erase({a,b});
		}else{
			if(s.count({a,b})&&s.count({b,a}))cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	return 0;
}
