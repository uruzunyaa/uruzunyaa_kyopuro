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
    
    uniform_int_distribution<ll> dist_N(4, 10);
    ll n = dist_N(rnd);
	
	vl q,d;
	loop(i,2,n){
		uniform_int_distribution<ll> dist_tmp(1, i-1);
		q.push_back(dist_tmp(rnd));
	}

	uniform_int_distribution<ll> dist_d(1, n);
    loop(i,1,n){
		d.push_back(dist_d(rnd));
	}

    cout << n << " "<< 1 << " "<<n<<" "<<1<<"\n";
    rep(i,n-1) cout << q[i]<<" ";
	cout<<endl;
	rep(i,n) cout << d[i]<<" ";
	cout<<endl;
    return 0;
}