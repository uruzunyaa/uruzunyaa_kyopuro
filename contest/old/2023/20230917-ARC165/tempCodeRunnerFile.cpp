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
	vl a(n);
	rep(i,n)cin>>a[i];
	//単調増加の最大数を判定。
	ll cnt=1;
	ll mx=1;
	rep(i,n-1){
		if(a[i]<a[i+1])cnt++;
		else cnt=1;
		mx=max(mx,cnt);
	}
	if(mx>=k){
		vdbg(a);
		return 0;
	}
	set<ll> s;
	loop(i,1,k)s.insert(a[n-i]);
	ll index=n-k;

	for(;index>0;index--){
		if(a[index-1]>*s.begin())break;
		s.insert(a[index-1]);
		s.erase(a[index+k-1]);
	}

	sort(a.begin()+index,a.begin()+index+k);
	vdbg(a);
	return 0;
}
