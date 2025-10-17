#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

//小数点切り捨ての√を求める。
ll introot(ll n) {
	if (n < 0) return false;
	ll sqrtN = static_cast<ll>(sqrt(n));
	ll ans=0;
	loop(i,max(0LL,sqrtN-2),sqrtN+2){
		if(i * i <= n)ans=i;
	}
	return ans;
}

int main(){

	return 0;
}
