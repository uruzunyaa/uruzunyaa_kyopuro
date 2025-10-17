#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

//ax+by=cの整数解を得る ただし、cはgcd(a,b)の倍数でない場合、0,0になる
pair<ll,ll> ex_euclid(ll a,ll b,ll c){
	if(a<0||b<0||c<0){
		pair<ll,ll>ans=ex_euclid(abs(a),abs(b),abs(c));
		if(a<0)ans.first*=-1;
		if(b<0)ans.second*=-1;
		if(c<0)ans.first*=-1,ans.second*=-1;
		return ans;
	}
	if(c!=1){
		ll d=gcd(a,b);
		if(c%d!=0)return make_pair(0,0);
		pair<ll,ll>ans = ex_euclid(a/d,b/d,1);
		ans.first*=c/d;
		ans.second*=c/d;
		return ans;
	}
	if(a<b){
		pair<ll,ll>ans=ex_euclid(b,a,c);
		swap(ans.first,ans.second);
		return ans;
	}
	if(a==1&&b==0)return make_pair(1,0);
	else if(b==0) return make_pair(0,0);
	ll x,y;
	tie(x,y)=ex_euclid(b,a%b,c);
	pair<ll,ll> ans=make_pair(y,x-(a/b)*y);
	return ans;
}


int main(){

	return 0;
}
