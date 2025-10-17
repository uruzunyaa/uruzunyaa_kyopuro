#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

ll inversion_number(vl &v) {
    int N = v.size();
    if (N == 1) return 0;
    vl v1(v.begin(), v.begin() + N / 2);
    vl v2(v.begin() + N / 2, v.end());
    ll res = inversion_number(v1) + inversion_number(v2);
    int p = 0, q = 0;
    for (int i = 0; i < N; i++) {
        if (q == v2.size() || (p < v1.size() && v1[p] <= v2[q])) {
            v[i] = v1[p++];
        }
        else {
            v[i] = v2[q++];
            res += v1.size() - p;
        }
    }
    return res;
}
int main()
{
	
	ll n,m;
	cin>>n>>m;
	vl a(n);
	vvl r(m+1);
	rep(i,n){
		cin >> a[i];
		r[m-a[i]-1].push_back(i);
	}
	
	ll tnto = inversion_number(a);

	rep(i,m){
		cout<<tnto<<endl;
		rep(j,r[i].size()){
			tnto+=r[i][j];
			tnto-=n-r[i][j]-1;
		}
	}
	return 0;
}

