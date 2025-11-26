#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n-1; i >=0; i--)
#define loop(i,m,n)for(ll i=m;i<=n;i++)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000000000000LL
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;


//行列Aと行列Bの積を計算する。
vvl matrix_product(vvl a,vvl b){
	//a[0].size()==b.size()を前提とする。
	ll n = a.size();
    ll m = b[0].size();
    ll l = b.size();

    vvl ans(n, vl(m, 0));

    rep(i, n){
        rep(j, m){
            ll sum = 0;
            rep(k, l){
                sum += a[i][k] * b[k][j];
            }
            ans[i][j] = sum;
        }
    }
    return ans;
}

int main(){
	vvl a={
		{1,2},
		{3,1},
		{3,2}
	};
	vvl b={
		{1,3,5},
		{2,4,1}
	};
	vvl ans=matrix_product(a,b);
	vvdbg(ans);
}