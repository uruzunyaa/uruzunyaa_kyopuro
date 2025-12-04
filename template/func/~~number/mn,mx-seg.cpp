#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

//配列AのMaxsubsegを返す
ll mxseg(vl a){
	ll mn=0;
	ll sum=0;
	ll ans=0;
	rep(i,a.size()){
		sum+=a[i];
		mn=min(mn,sum);
		ans=max(sum-mn,ans);
	}
	return ans;
}

//配列AのMinsubsegを返す
ll mnseg(vl a){
	ll mx=0;
	ll sum=0;
	ll ans=0;
	rep(i,a.size()){
		sum+=a[i];
		mx=max(mx,sum);
		ans=min(sum-mx,ans);
	}
	return ans;
}

int main(){

	return 0;
}
