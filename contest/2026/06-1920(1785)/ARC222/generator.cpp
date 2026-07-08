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
    
    uniform_int_distribution<ll> dist_N(0, 4);
    ll a = dist_N(rnd);
    ll b = dist_N(rnd);
    ll c = dist_N(rnd);
    if(a+b+c<3){
        c+=3;
    }
	

	cout<<1<<"\n";
    cout << a << " "<< b <<" "<< c <<"\n";
    return 0;
}