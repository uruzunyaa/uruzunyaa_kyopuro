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

//指数型母関数の畳み込み前、重み付けをする
vl makeinv(vl a){
	ll fact=1;
	loop(i,1,a.size()-1){
		fact*=i;
		fact%=md;
		ll invfact=power_mod(fact,md-2);
		a[i]*=invfact;
		a[i]%=md;
	}
	return a;
}

//指数型母関数の畳み込み後、重み付けを解除する
vl restoreinv(vl a){
	ll fact=1;
	loop(i,1,a.size()-1){
		fact*=i;
		fact%=md;

		a[i]*=fact;
		a[i]%=md;
	}
	return a;
}

//指数の重み付けをした畳み込み,指数型母関数
vl invconv(vl a,vl b){

	a=makeinv(a);
	b=makeinv(b);

	vl ans=atcoder::convolution<998244353>(a,b);
	
	ans=restoreinv(ans);

	return ans;
}



//メイン
void solve(ll n){

	vl red(n+1,1);
	vl blue(n+1,0),yellow(n+1,0);
	rep(i,n+1){
		if(i%2==0)blue[i]=1;
		else yellow[i]=1;
	}

	red=makeinv(red);
	blue=makeinv(blue);
	yellow=makeinv(yellow);
	
	vl tmp=atcoder::convolution<998244353>(red,blue);
	vl ans=atcoder::convolution<998244353>(yellow,tmp);
	
	
	ans=restoreinv(ans);
	
	cout<<ans[n]<<endl;
	return;
}

int main(){
	ll n;
	cin>>n;
	loop(i,1,n){
		cout<<i<<":";
		solve(i);
	}
	return 0;
}
