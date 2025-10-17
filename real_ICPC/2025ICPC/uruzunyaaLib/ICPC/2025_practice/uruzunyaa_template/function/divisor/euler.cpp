#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

//オイラーのトーシェント関数。N以下のNと互いに素な物の数を返す。
ll euler(ll n){
	unordered_map<ll,ll> factors;
	ll tmp=n;
	while (tmp % 2 == 0) {
		factors[2]++;
		tmp /= 2;
	}
	for (ll i=3; i*i<=tmp;i+=2) {
		while (tmp%i == 0) {
			factors[i]++;
			tmp/= i;
		}
	}
	if (tmp > 2)factors[tmp]++;
	ll ans=1;
	for(const auto & val:factors){
		ans*=(val.first-1);
		rep(j,val.second-1)ans*=val.first;
	}
	return ans;
}

int main(){

	return 0;
}
