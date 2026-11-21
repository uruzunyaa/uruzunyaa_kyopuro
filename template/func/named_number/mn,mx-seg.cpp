#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL

//配列AのMaxsubsegを返す。
//空集合を認める。
ll mxseg(vl a){
	ll mn=0;
	ll sum=0;
	//空集合禁止の時はans初期値を-infにする事。
	ll ans=0;
	rep(i,a.size()){
		sum+=a[i];
		//この下の2行を入れ替えると、空集合が禁止になる。
		mn=min(mn,sum);
		ans=max(sum-mn,ans);
	}
	return ans;
}

//配列AのMinsubsegを返す。
//空集合を認める。
ll mnseg(vl a){
	ll mx=0;
	ll sum=0;
	//空集合禁止の時はans初期値をinfにする事。
	ll ans=0;
	rep(i,a.size()){
		sum+=a[i];
		//この下の2行を入れ替えると、空集合が禁止になる。
		mx=max(mx,sum);
		ans=min(sum-mx,ans);
	}
	return ans;
}

int main(){

	return 0;
}
