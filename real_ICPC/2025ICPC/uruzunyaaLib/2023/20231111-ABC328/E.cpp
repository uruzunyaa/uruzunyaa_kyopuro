#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cmath>
#include<fstream>
#include<random>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000
#define mod 998244353
//#define mod 1000000007
//√の値が整数かを調べる
bool isSqrt(ll n) {
	if (n < 0) return false;
	ll sqrtN = static_cast<ll>(sqrt(n));
	return sqrtN * sqrtN == n;
}
//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}
//素因数分解
vector<ll> makePrime(ll n){
	vector<ll> factors;
	while (n % 2 == 0) {
		factors.push_back(2);
		n /= 2;
	}
	for (ll i=3; i*i<=n;i+=2) {
		while (n%i == 0) {
			factors.push_back(i);
			n /= i;
		}
	}
	if (n > 2) {
		factors.push_back(n);
	}
	return factors;
}
// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k) {
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}
//場合の数 nCr を求める
ll ncr(ll n,ll r) {
	vvl dp(n+1,vl(r+1));
	rep (i,n+1)dp[i][0] = 1;
	rep (i,r+1)dp[i][i] = 1;
	loop (i,1,n){
		loop (j,1,min((ll)i-1,r)) {
			//nCr= n-1Cr-1 + n-1Cr
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
		}
	}
	return dp[n][r];
}

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
ifstream fin("./DefaultFile");
ofstream fout("./DefaultFile");//出力する場合の出力先を指定

int main(){
	ll n,m,k;
	cin>>n>>m>>k;
	vl u(m);
	vl v(m);
	vl w(m);
	rep(i,m){
		cin>>u[i]>>v[i]>>w[i];
	}
	vl find(n,-1);
	vl check(m,0);
	ll wmax = 0;
	ll ans=0;
	rep(i,m)if(w[wmax]<w[i])wmax=i;
	rep(i,n-1){
		vl nokori;
		rep(i,m)if(check[i]==0)nokori.push_back(i);
		ll mn=wmax;
		rep(i,nokori.size()){
			if(find[u[nokori[i]]]!=find[v[nokori[i]]]||find[v[nokori[i]]]==-1){
				if(w[mn]>w[nokori[i]])mn=nokori[i];
			}
		}
		if(find[u[mn]]==-1){
			if(find[v[mn]]==-1){
				find[u[mn]]=find[v[mn]]=v[mn];
			}else{
				find[u[mn]]=find[v[mn]];
			}
		}else{
			if(find[v[mn]]==-1){
				find[v[mn]]=find[u[mn]];
			}else{
				ll temp=find[u[mn]];
				rep(i,n){
					if(find[i]==temp)find[i]=find[v[mn]];
				}
			}
		}
		check[mn]=1;
		cout<<w[mn]<<endl;
		ans+=w[mn];
		ans%=k;
	}
	cout<<ans<<endl;

}