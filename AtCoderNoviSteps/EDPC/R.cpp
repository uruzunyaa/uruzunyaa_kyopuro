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

//行列累乗前提関数
vvl matrix_mul_mod(vvl a,vvl b,ll md){
	//a[0].size()==b.size()を前提とする。
	ll n = a.size();
    vvl ans(n, vl(n, 0));
    rep(i, n){
        rep(j, n){
            ll sum = 0;
            rep(k, n){
                sum += a[i][k] * b[k][j];
				sum%=md;
            }
            ans[i][j] = sum;
        }
    }
    return ans;
}

// 行列aのk乗をmで割った余りを計算
vvl matrix_pow(vvl a, ll k,ll md){
	ll n=a.size();
	vvl ans(n,vl(n,0));
	rep(i,n)ans[i][i]=1;
	while (k > 0){
		if ((k&1) ==1)ans=matrix_mul_mod(ans,a,md);
		a=matrix_mul_mod(a,a,md);
		k >>= 1;
	}
	return ans;
}

int main(){
	ll n,k;
	cin>>n>>k;
	vvl a(n,vl(n));
	rep(i,n)rep(j,n)cin>>a[i][j];
	a=matrix_pow(a,k,1000000007);
	ll ans=0;
	rep(i,n)rep(j,n)ans+=a[i][j];
	ans%=1000000007;
	cout<<ans<<endl;
}