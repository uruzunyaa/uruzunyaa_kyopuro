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
	ll x,a,d,n;
	cin>>x>>a>>d>>n;
	ll last=a+(d-1)*n;
	
	if(d<0){
		swap(a,last);
		d*=-1;
	}

	if(x<a){
		cout<<a-x<<endl;
		return 0;
	}
	if(last<x){
		cout<<x-last<<endl;
		return 0;
	}

	a%=d;
	a+=d;
	a%=d;
	x%=d;
	x+=d;
	x%=d;
	
	if(a<x)swap(a,x);

	cout<<min(a-x,x+d-a)<<endl;
	return 0;
}
