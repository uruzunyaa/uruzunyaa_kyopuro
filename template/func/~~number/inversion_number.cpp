#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL

//転倒数を求める
ll inversion_number(vl &v) {
	int n = v.size();
	if (n == 1) return 0;
	vl v1(v.begin(), v.begin() + n / 2);
	vl v2(v.begin() + n / 2, v.end());
	ll res = inversion_number(v1) + inversion_number(v2);
	int p = 0, q = 0;
	for (int i = 0; i < n; i++) {
		if (q == v2.size() || (p < v1.size() && v1[p] <= v2[q])) {
			v[i] = v1[p++];
		}else {
			v[i] = v2[q++];
			res += v1.size() - p;
		}
    }
    return res;
}

//メイン
int main(){
	
	return 0;
}
