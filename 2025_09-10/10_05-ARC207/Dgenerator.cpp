#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
int main(){
    random_device seed_gen;
    mt19937_64 rnd(seed_gen());
    
    uniform_int_distribution<ll> dist_NM(1, 5),dist_A(0,1);
    ll N = dist_NM(rnd);
	ll M = dist_NM(rnd);
    vector<string> A(N);
    rep(i,N) {
		rep(j,M){
			A[i].push_back(dist_A(rnd)+'0');
		}
	}
	cout<<1<<"\n";
    cout << N <<" "<<M<<"\n";
    rep(i,N) cout << A[i] << "\n";
    return 0;
}