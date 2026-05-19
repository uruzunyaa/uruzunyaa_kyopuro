#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>

//N頂点のグラフを生成する例。
int main(){
    random_device seed_gen;
    mt19937_64 rnd(seed_gen());
    
    uniform_int_distribution<ll> dist_N(1, 4);
    uniform_int_distribution<ll> dist_s(0, 25);
    
    ll n = dist_N(rnd);
    ll k = dist_N(rnd);
	
	//ここから先は問題固有
    vector<string> s(k);
    rep(i,k){
        ll siz=dist_N(rnd);
        rep(z,siz){
            ll tmp=dist_s(rnd);
            s[i].push_back('a'+tmp);
        }
    }

    cout << n << " "<< k<<"\n";
    rep(i,k) cout << s[i]<<"\n";
    return 0;
}