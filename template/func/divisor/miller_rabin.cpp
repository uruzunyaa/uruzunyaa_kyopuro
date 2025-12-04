#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
 
//ll型の素数判定,defineのmodを必ず切る事。
const unsigned ll numset[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022ULL}; // 少なくとも 2^64 までは決定的

unsigned ll mod_mul(unsigned ll a, unsigned ll b, unsigned ll mod) {
	ll ret = a * b - mod * (unsigned ll)((long double)(a) * (long double)(b) / (long double)(mod));
	return ret + mod * (ret < 0) - mod * (ret >= (ll)mod);
}
 
unsigned ll mod_pow(unsigned ll x, unsigned ll k, unsigned ll mod){
    unsigned ll res = 1;
    while(k){
        if(k & 1) res = mod_mul(res, x, mod);
        x = mod_mul(x, x, mod);
        k >>= 1;
    }
    return res;
}
 
bool miller_rabin(unsigned ll n){
    if(n < 2 || ((n % 6 != 1) && (n % 6 != 5))) return (n == 2) || (n == 3);
    unsigned ll d = n - 1, s = 0;
    while(d % 2 == 0){
        d /= 2;
        s++;
    }
    for(unsigned ll a : numset){
        if(a % n == 0) return true;
        unsigned ll res = mod_pow(a, d, n);
        if(res == 1) continue;
        bool ok = true;
        for(unsigned int r = 0; r < s; r++){
            if(res == n-1){
                ok = false;
                break;
            }
            res = mod_mul(res, res, n);
        }
        if(ok) return false;
    }
    return true;
}

int main(){

	return 0;
}
