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
#define mod 998244353LL
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

void ntt(vector<long long> &a, bool invert){
	int n = (int)a.size();
	static const long long g = 3; // 998244353の原始根

	// ビット反転置換
	for(int i=1,j=0;i<n;i++){
		int bit=n>>1;
		for(;j&bit;bit>>=1)j^=bit;
		j^=bit;
		if(i<j)swap(a[i],a[j]);
	}

	for(int len=2;len<=n;len<<=1){
		long long wlen = power_mod(g, (mod-1)/len);
		if(invert) wlen = power_mod(wlen, mod-2);
		for(int i=0;i<n;i+=len){
			long long w=1;
			for(int j=0;j<len/2;j++){
				long long u=a[i+j], v=a[i+j+len/2]*w%mod;
				a[i+j]=(u+v)%mod;
				a[i+j+len/2]=(u-v+mod)%mod;
				w=w*wlen%mod;
			}
		}
	}

	if(invert){
		long long inv_n = power_mod(n, mod-2);
		for(long long &x : a) x = x * inv_n % mod;
	}
}

vector<long long> convolution(const vector<long long> &A, const vector<long long> &B){
	vector<long long> a=A,b=B;
	int n=1;
	while(n<(int)a.size()+(int)b.size()-1) n<<=1;
	a.resize(n); b.resize(n);

	ntt(a,false);
	ntt(b,false);
	for(int i=0;i<n;i++) a[i]=a[i]*b[i]%mod;
	ntt(a,true);
	a.resize(A.size()+B.size()-1);
	return a;
}


//通常型母関数aのk乗の指数n項まで計算する。
vl powconv(vl a,ll k,ll n){
	vl result = {1};
	while (k > 0){
		if ((k&1) ==1){
			result=convolution(result,a);
			while(result.size()>n+1)result.pop_back();
		}
		a=convolution(a,a);
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
		fact%=mod;
		ll invfact=power_mod(i,mod-2);
		a[i]*=invfact;
	}

	fact=1;
	loop(i,1,b.size()-1){
		fact*=i;
		fact%=mod;
		ll invfact=power_mod(i,mod-2);
		b[i]*=invfact;
	}

	vl ans=convolution(a,b);
	
	fact=1;
	loop(i,1,ans.size()-1){
		fact*=i;
		fact%=mod;

		ans[i]*=fact;
		ans[i]%=mod;
	}

	return ans;
}



//メイン
int main(){
	ll d,n;
	cin>>d>>n;

	vl a={0,1,0,1,1,0,1};
	cout<<powconv(a,d,n).back()<<endl;
	return 0;
}
