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

//最も直近の自分以上の数値を持つindexを返す。
//自分がprefixで真に最大の時は-1
vl nearest_greater_equal(vl a){
	ll n=a.size();
	vl mae(n);
	vector<pair<ll,ll>> tmp;
	tmp.push_back({inf,-1});
	rep(i,n){
		while(tmp.back().first<a[i])tmp.pop_back();
		mae[i]=tmp.back().second;
		tmp.push_back({a[i],i});
	}
	return mae;
}

//最も直近の自分より真に大きい数値を持つindexを返す。
//自分がprefixで最大のうちの1つである時は-1
vl nearest_greater(vl a){
	ll n=a.size();
	vl mae(n);
	vector<pair<ll,ll>> tmp;
	tmp.push_back({inf,-1});
	rep(i,n){
		while(tmp.back().first<=a[i])tmp.pop_back();
		mae[i]=tmp.back().second;
		tmp.push_back({a[i],i});
	}
	return mae;
}

//最も直近の自分以下の数値を持つindexを返す。
//自分がprefixで真に最小の時は-1
vl nearest_less_equal(vl a){
	ll n=a.size();
	vl mae(n);
	vector<pair<ll,ll>> tmp;
	tmp.push_back({-inf,-1});
	rep(i,n){
		while(tmp.back().first>a[i])tmp.pop_back();
		mae[i]=tmp.back().second;
		tmp.push_back({a[i],i});
	}
	return mae;
}

//最も直近の自分より真に小さい数値を持つindexを返す。
//自分がprefixで最小のうちの1つである時は-1
vl nearest_less(vl a){
	ll n=a.size();
	vl mae(n);
	vector<pair<ll,ll>> tmp;
	tmp.push_back({-inf,-1});
	rep(i,n){
		while(tmp.back().first>=a[i])tmp.pop_back();
		mae[i]=tmp.back().second;
		tmp.push_back({a[i],i});
	}
	return mae;
}

int main(){
	
	return 0;
}