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
    ll n = dist_N(rnd);

    uniform_int_distribution<ll> dist_ab(1, n);
    vl a(n),b(n);

    rep(i,n)a[i]=dist_ab(rnd);
    rep(i,n)b[i]=dist_ab(rnd);

    cout<<"1\n";
    cout << n << "\n";
    rep(i,n) cout << a[i]<<" ";
    cout<<"\n";
    rep(i,n) cout << b[i]<<" ";
    cout<<"\n";
    return 0;
}