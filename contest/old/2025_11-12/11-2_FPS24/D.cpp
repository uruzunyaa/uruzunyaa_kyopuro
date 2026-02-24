//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
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

//#define mod 1000000007LL
#define eps 0.000000001

// nのk乗をmodで割った余りを計算(ACLと競合しないようにmodを使ってない)
#define md 998244353LL
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%md;
		n=n*n%md;
		k >>= 1;
	}
	return result;
}


#include <atcoder/convolution>
//通常型母関数aのk乗の指数n項まで計算する。
vl powconv(vl a,ll k,ll n){
	vl result = {1};
	while (k > 0){
		if ((k&1) ==1){
			result=atcoder::convolution<998244353>(result,a);
			while(result.size()>n+1)result.pop_back();
		}
		a=atcoder::convolution<998244353>(a,a);
		k >>= 1;
		while(a.size()>n+1)a.pop_back();
	}
	return result;
}

//指数の重み付けをした畳み込み,指数型母関数
vl invconv(vl a,vl b){
	ll fact=1;
	loop(i,1,a.size()-1){
		fact*=i;
		fact%=md;
		ll invfact=power_mod(i,md-2);
		a[i]*=invfact;
	}

	fact=1;
	loop(i,1,b.size()-1){
		fact*=i;
		fact%=md;
		ll invfact=power_mod(i,md-2);
		b[i]*=invfact;
	}

	vl ans=atcoder::convolution<998244353>(a,b);
	
	fact=1;
	loop(i,1,ans.size()-1){
		fact*=i;
		fact%=md;

		ans[i]*=fact;
		ans[i]%=md;
	}

	return ans;
}



//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl firsts(m+1,1);
	vl a(m+1);
	rep(i,m+1){
		if(i%2==1)a[i]=1;
		else a[i]=0;
	}
	vl tmp=powconv(a,n-1,m);
	vl ans=atcoder::convolution<998244353>(firsts,tmp);
	
	ll sum=0;
	rep(i,m+1){
		sum+=ans[i];
	}
	sum%=md;

	loop(i,1,n){
		sum*=i;
		sum%=md;
	}


	cout<<sum<<endl;
	return 0;
}
