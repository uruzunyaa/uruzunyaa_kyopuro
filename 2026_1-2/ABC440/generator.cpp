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
    
    uniform_int_distribution<ll> dist_FHW(1, 5);
	uniform_int_distribution<ll> dist_sv(0, 20);
    ll f = dist_FHW(rnd);
	ll h = dist_FHW(rnd);
	ll w = dist_FHW(rnd);
	
	
	
    cout << f << " " <<h<<" "<<w<<"\n";
    rep(i,f*h){
		rep(j,w){
			ll num=dist_sv(rnd);
			if(num>=10){
				cout<<'#';
			}else{
				cout<<num;
			}
		}
		cout<<"\n";
	}
	cout<<"1\n";

	uniform_int_distribution<ll> dist_F(1, f);
    ll g = dist_F(rnd);
	uniform_int_distribution<ll> dist_H(1, h);
    ll a = dist_H(rnd);
	uniform_int_distribution<ll> dist_W(1, w);
    ll b = dist_W(rnd);

	cout<<g<<" "<<a<<" "<<b<<"\n";
    return 0;
}