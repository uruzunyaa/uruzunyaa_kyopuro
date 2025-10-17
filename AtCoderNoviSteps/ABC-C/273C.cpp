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
	map<ll,ll> a;
	rep(i,n){
		
		ll aa;
		cin>>aa;

		a[aa]++;
	}

	ll k;
	auto it=a.end();
	rep(i,n){
		if(it==a.begin()){
			rep(j,n-i){
				cout<<0<<endl;
			}
			break;
		}
		it--;
		cout<<it->second<<endl;
	}
	return 0;
}
