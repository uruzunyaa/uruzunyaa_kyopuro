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
    
    uniform_int_distribution<ll> dist_N(1, 8);
    ll n = dist_N(rnd);
	ll pw=1;
    rep(i,n)pw*=n;

	uniform_int_distribution<ll> dist_nex(1, pw);
    ll pm=dist_nex(rnd);
    vl a;
    rep(i,n)a.push_back(i+1);

    rep(i,pm){
        next_permutation(a.begin(),a.end());
    }

	cout<<n<<"\n";
    rep(i,n)cout<<a[i]<<" ";
    cout<<"\n";
    return 0;
}