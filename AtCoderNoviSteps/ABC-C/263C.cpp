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

void func(ll n,ll mn,ll mx,vl & tmp){
	if(n==tmp.size()){
		vdbg(tmp);
		return ;
	}
	loop(i,mn,mx){
		tmp.push_back(i);
		func(n,i+1,mx,tmp);
		tmp.pop_back();
	}
	return ;
}

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl tmp;
	func(n,1,m,tmp);
	return 0;
}
