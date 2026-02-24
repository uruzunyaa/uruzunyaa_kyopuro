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
    
    uniform_int_distribution<ll> dist_N(1, 12);
    ll n = dist_N(rnd);
	
	//ここから先は問題固有
	uniform_int_distribution<ll> dist_s(0,6);
    string s;
	ll cnt=0;
	s.push_back('A');
	rep(i,n-2){
		ll tmp=dist_s(rnd);
		if(tmp>=3){
			s.push_back('?');
			cnt++;
		}else{
			s.push_back('A'+tmp);
		}
	}
	s.push_back('A');

	uniform_int_distribution<ll> dist_x(0,cnt);
	ll x=dist_x(rnd);
	uniform_int_distribution<ll> dist_y(0,cnt-x);
	ll y=dist_y(rnd);
	ll z=cnt-x-y;
	
	cout<<n<<"\n";
	cout<<s<<"\n";
    cout << 1 <<"\n";
    cout<<x<<" "<<y<<" "<<z<<"\n";
	return 0;
}