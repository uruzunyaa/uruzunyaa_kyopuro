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
	ll n;
	cin>>n;
	vl a(n);
	unordered_set<ll> s;
	rep(i,n){
		cin>>a[i];
		if(s.count(a[i]))a[i]=inf;
		else s.insert(a[i]);
	}
	sort(a.begin(),a.end());
	ll ans=0;
	rep(i,n){
		if(i>=a.size())break;
		if(a[i]==ans+1)ans++;
		else{
			if(a.size()>=i+2){
				ans++;
				i--;
				a.pop_back();
				a.pop_back();
			}else{
				break;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
