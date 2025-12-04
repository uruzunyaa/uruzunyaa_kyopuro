#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n-1; i >=0; i--)
#define loop(i,m,n)for(ll i=m;i<=n;i++)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000000000000LL

//行列累乗前提関数
vvl matrix_mul_md(vvl a,vvl b,ll md){
	//a,bが全て同一値の正方行列である事を前提とする
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
		if ((k&1) ==1)ans=matrix_mul_md(ans,a,md);
		a=matrix_mul_md(a,a,md);
		k >>= 1;
	}
	return ans;
}

int main(){
	
}