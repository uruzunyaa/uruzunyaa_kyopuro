#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

//map形式で、nを素因数分解した値を返す
map<ll,ll> makeMapPrime(ll n){
	map<ll,ll> factors;
	while (n % 2 == 0) {
		factors[2]++;
		n /= 2;
	}
	for (ll i=3; i*i<=n;i+=2) {
		while (n%i == 0) {
			factors[i]++;
			n /= i;
		}
	}
	if (n > 2) {
		factors[n]++;
	}
	return factors;
}

int main(){

	return 0;
}
