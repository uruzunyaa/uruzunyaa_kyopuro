#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cmath>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define ll long long
#define inf 4000000000000000000
//√の値が整数かを調べる
bool isSqrt(ll n) {
	if (n < 0) return false;
	ll sqrtN = static_cast<ll>(sqrt(n));
	return sqrtN * sqrtN == n;
}
//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i = 0; i < B; i++) {
		result *= A;
	}
	return result;
}
//素因数分解
vector<ll> makePrime(ll n) {
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

int main(){
    int n;
	cin>>n;
    ll w[n],x[n];
    rep(i,n) cin>>w[i]>>x[i];
    ll mx=0;
    rep(i,24){
    ll p=0;
        rep(j,n){
            if(9<=(i+x[j])%24&&17>=(i+x[j])%24)p+=w[j];
        }
        mx=max(mx,p);
    }
    cout<<mx<<endl;
    return 0;
}