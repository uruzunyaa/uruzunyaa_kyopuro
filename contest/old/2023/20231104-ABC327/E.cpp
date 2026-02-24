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
#define inf 2000000000
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

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
ifstream fin("./DefaultFile");
ofstream fout("./DefaultFile");//出力する場合の出力先を指定

int main(){
    int n;
    cin>>n;
    int p[n];
    rep(i,n)cin>>p[i];

    //dp[i][j]はi個のコンテストを考慮して、j個のコンテストに出た時の最善値。
    vector<vector<double>> dp(n+1,vector<double>(n+1,-inf));
    loop(i,1,n){
        //iは考慮するコンテストの数

        //前のコピー
        loop(j,1,n)dp[i][j]=dp[i-1][j];
        
        //更新
        if(dp[i][1]<p[n-i])dp[i][1]=p[n-i];
        loop(j,2,n){
            dp[i][j]=max(dp[i][j],dp[i-1][j-1]+pow(0.9,j-1)*p[n-i]);
        }
    }
    double mx=-inf;
    double bunbo=1;
    //cout<<dp[n][2]<<endl;
    loop(i,1,n){
        double r=dp[n][i]/bunbo-1200.0/sqrt(i);
        mx=max(r,mx);
        bunbo+=pow(0.9,i);
    }

    cout<<fixed<<setprecision(10)<<mx<<endl;

    return 0;
}