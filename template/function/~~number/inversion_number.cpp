#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

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
