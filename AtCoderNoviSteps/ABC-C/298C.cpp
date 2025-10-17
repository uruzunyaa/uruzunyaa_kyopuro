#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353LL
int main(){
	ll n,q;
	cin>>n>>q;
	vector<multiset<ll>> hako(n+1);
	vector<set<ll>> card(200001);
	rep(z,q){
		ll t;
		cin>>t;
		if(t==1){
			ll i,j;
			cin>>i>>j;
			hako[j].insert(i);
			card[i].insert(j);
		}else if(t==2){
			ll i;
			cin>>i;
			for(const auto &val:hako[i]){
				cout<<val<<" ";
			}
			cout<<endl;
		}else{
			ll i;
			cin>>i;
			for(const auto &val:card[i]){
				cout<<val<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}