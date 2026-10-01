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
    
    uniform_int_distribution<ll> dist_NM(2, 8);
    ll n = dist_NM(rnd);
    ll m = dist_NM(rnd);
	
	//ここから先は問題固有
	uniform_int_distribution<ll> dist_r(1,n);
    vl a,b;
    rep(i,m){
        ll aa=dist_r(rnd),bb=dist_r(rnd);
        while(aa==bb){
            aa=dist_r(rnd);
            bb=dist_r(rnd);
        }
        if(aa>bb)swap(aa,bb);
        a.push_back(aa);
        b.push_back(bb);
    }
    cout << n << " "<< m<<"\n";
    rep(i,m) cout << a[i] << " "<<b[i]<<"\n";
    return 0;
}