#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#include<atcoder/lazysegtree>

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

int main(){
	ll n;
	cin>>n;
	string s;
	cin>>s;

	vl a;
	ll sums=0;
	a.push_back(0);
	rep(i,n){
		if(s[i]=='A')sums++;
		else sums--;
		a.push_back(sums);
	}
	
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
	ll q;
	cin>>q;
	while(q--){
		ll t;
		cin>>t;
		if(t==1){
			ll i;
			char c;
			cin>>i>>c;
			i--;
			
			ll tmp;
			if(s[i]=='A')tmp=-1;
			else tmp=1;
			seg.apply(i+1,n,tmp);
			
			s[i]=c;

			if(s[i]=='A')tmp=1;
			else tmp=-1;
			seg.apply(i+1,n,tmp);
		}else{
			ll l,r;
			cin>>l>>r;
			l--;
			r++;
			if(seg.get(l)==seg.prod(l,r))cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	return 0;
}