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

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
ifstream fin("./DefaultFile");
ofstream fout("./DefaultFile");//出力する場合の出力先を指定

int main(){
    ll b;
    cin>>b;
    ll a=0;
    do{
        a++;
        if(power(a,a)==b){
            cout<<a<<endl;
            return 0;
        }
    }while(power(a,a)<=b/a);

    cout<<-1<<endl;
    return 0;
}