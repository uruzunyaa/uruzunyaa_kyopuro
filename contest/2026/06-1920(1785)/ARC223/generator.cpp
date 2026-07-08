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
    
    uniform_int_distribution<ll> dist_N(1, 6);
    uniform_int_distribution<ll> dist_M(0, 6);
    uniform_int_distribution<ll> dist_AB(0, 1);
    
    
    ll n = dist_N(rnd);
    ll m = dist_M(rnd)+n;
    vl a(n);
    vl b(m);
    rep(i,n){
        a[i]=dist_AB(rnd);
    }
    rep(i,m){
        b[i]=dist_AB(rnd);
    }

	cout<<1<<"\n";
    cout << n << " "<< m <<"\n";
    rep(i,n)cout<<a[i]<<" ";
    cout<<"\n";
    rep(i,m)cout<<b[i]<<" ";
    cout<<"\n";
    return 0;
}