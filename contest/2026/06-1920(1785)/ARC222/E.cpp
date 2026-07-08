#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define mod 998244353LL

// --------- XOR Convolution ---------

// Hadamard transform for XOR convolution
// inplace: a -> H a
inline void fwht_xor_ll(vector<__int128> &a){
    int n = (int)a.size();
    for (int len = 1; len < n; len <<= 1){
        for (int i = 0; i < n; i += (len << 1)){
            for (int j = 0; j < len; j++){
                __int128 x = a[i + j];
                __int128 y = a[i + j + len];
                a[i + j]       = x + y;
                a[i + j + len] = x - y;
            }
        }
    }
}

// 公開: xor_convolution_ll
// c[k] = Σ a[i] * b[j] such that (i xor j) == k
inline vector<ll> xor_convolution_ll(const vector<ll> &a, const vector<ll> &b){
    int n = (int)a.size(), m = (int)b.size();
    if (!n || !m) return {};

    int sz = 1;
    while (sz < max(n, m)) sz <<= 1;

    vector<__int128> fa(sz), fb(sz);
    for (int i = 0; i < n; i++) fa[i] = a[i];
    for (int i = 0; i < m; i++) fb[i] = b[i];

    fwht_xor_ll(fa);
    fwht_xor_ll(fb);

    for (int i = 0; i < sz; i++){
        fa[i] *= fb[i];
    }

    // inverse FWHT is same transform divided by sz
    fwht_xor_ll(fa);

    vector<ll> c(sz);
    for (int i = 0; i < sz; i++){
        fa[i] /= sz;
        c[i] = (ll)fa[i];
    }

    return c;
}

int main(){
	ll n,m;
	cin>>n>>m;
	m=(1LL<<m);
	vl a(m,0);
	rep(i,n){
		ll aa;
		cin>>aa;
		a[aa]++;
	}

	vl ans(m,0);
	rep(j,m){
		ans[0]+=a[j]/2;
	}

	loop(i,1,30){
		vl b(m);
		rep(j,m){
			b[j]=min(a[j],1LL);
		}
		vl tmp=xor_convolution_ll(b,b);
		loop(j,1,m-1){
			ans[j]+=tmp[j]/2;
		}
		rep(j,m){
			a[j]=max(a[j]-1,0LL);
		}
	}

	vl indlist;
	
	rep(j,m){
		if(a[j]==0)continue;
		indlist.push_back(j);
	}
	rep(j,indlist.size()){
		rep(i,j){
			ll ni=indlist[i];
			ll nj=indlist[j];
			ans[ni^nj]+=min(a[ni],a[nj]);
		}
	}

	ll hash=0;
	ll now=1;
	rep(j,m){
		hash+=now*ans[j];
		hash%=mod;
		now*=10;
		now%=mod;
	}
	cout<<hash<<endl;
    return 0;
}