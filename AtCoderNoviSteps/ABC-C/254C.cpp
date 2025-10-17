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
	ll n,k;
	cin>>n>>k;
	vvl a(k);
	rep(i,n){
		ll aa;
		cin>>aa;
		a[i%k].push_back(aa);
	}
	rep(i,k){
		sort(a[i].begin(),a[i].end());
	}

	vl b(n);
	rep(i,n){
		b[i]=a[i%k][i/k];
	}

	vl c=b;
	sort(c.begin(),c.end());

	if(b==c)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
