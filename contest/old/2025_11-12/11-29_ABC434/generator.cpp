#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>

//N頂点のグラフを生成する。
int main(){
    random_device seed_gen;
    mt19937_64 rnd(seed_gen());
    
    uniform_int_distribution<ll> dist_N(2, 4);
    ll n = dist_N(rnd);
	
	//ここから先は問題固有
	uniform_int_distribution<ll> dist_r(1,6);
    

	cout<<1<<"\n";
	cout << n <<"\n";
	rep(i,n){
		ll siz=dist_r(rnd);
		
		rep(j,siz){
			char tmp=dist_r(rnd)+'a';
			cout<<tmp;
		}
		cout<<"\n";
	}
    return 0;
}