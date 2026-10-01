//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


// nのk乗をmodで割った余りを計算(modはdefineで定義想定)
ll power_mod(ll n, ll k){
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return ans;
}

inline void ntt_998(vector<ll> &a, bool invert){
    int n = (int)a.size();
    if (n == 0) return;

    // bit reversal
    for (int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    const ll g = 3; // primitive root for 998244353

    for (int len = 2; len <= n; len <<= 1){
        ll wlen = power_mod(g, (mod - 1) / len);
        if (invert){
            wlen = power_mod(wlen, mod - 2); // wlen^{-1}
        }
        for (int i = 0; i < n; i += len){
            ll w = 1;
            int half = len >> 1;
            for (int j = 0; j < half; j++){
                ll u = a[i + j];
                ll v = a[i + j + half] * w % mod;
                ll x = u + v;
                if (x >= mod) x -= mod;
                ll y = u - v;
                if (y < 0) y += mod;
                a[i + j]         = x;
                a[i + j + half]  = y;
                w = w * wlen % mod;
            }
        }
    }

    if (invert){
        ll inv_n = power_mod(n, mod - 2);
        for (int i = 0; i < n; i++){
            a[i] = a[i] * inv_n % mod;
        }
    }
}

// ----------------- 998244353 用 convolution -----------------

inline vector<ll> convolution(const vector<ll> &a, const vector<ll> &b){
    int n = (int)a.size(), m = (int)b.size();
    if (!n || !m) return {};

    // 小さい場合は愚直 O(nm)
    if (min(n, m) <= 60){
        vector<ll> c(n + m - 1, 0);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                ll x = (a[i] % mod + mod) % mod;
                ll y = (b[j] % mod + mod) % mod;
                c[i + j] = (c[i + j] + x * y) % mod;
            }
        }
        return c;
    }

    int sz = 1;
    while (sz < n + m - 1) sz <<= 1;
    vector<ll> fa(sz), fb(sz);
    for (int i = 0; i < n; i++){
        fa[i] = (a[i] % mod + mod) % mod;
    }
    for (int i = 0; i < m; i++){
        fb[i] = (b[i] % mod + mod) % mod;
    }

    ntt_998(fa, false);
    ntt_998(fb, false);
    for (int i = 0; i < sz; i++){
        fa[i] = fa[i] * fb[i] % mod;
    }
    ntt_998(fa, true);

    fa.resize(n + m - 1);
    return fa;
}


//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	k-=n;
	if(k<0||k>=n){
		cout<<0<<endl;
		return 0;
	}

	queue<vl> fps;
	loop(i,1,n){
		vl a={1,n-i};
		a[0]*=power_mod(n-i+1,mod-2);
		a[1]*=power_mod(n-i+1,mod-2);
		a[0]%=mod;
		a[1]%=mod;
		fps.push(a);
	}

	rep(i,n-1){
		vl first=fps.front();
		fps.pop();
		vl second=fps.front();
		fps.pop();
		vl nx=convolution(first,second);
		fps.push(nx);
	}

	cout<<fps.front()[k]<<endl;
	return 0;
}
