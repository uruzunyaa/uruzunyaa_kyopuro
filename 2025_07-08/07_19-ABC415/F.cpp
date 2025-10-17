#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

#include"atcoder/lazysegtree.hpp"

using S = long long;
using F = long long;

const S INF = 8e18;
const F ID = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return (f == ID ? x : f); }
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,q;
	cin>>n>>q;

	string s;
	cin>>s;

	set<ll> t;
	t.insert(0);

	vl v(n,0);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	loop(i,1,n-1){
		if(s[i]!=s[i-1]){
			ll tmp=*t.rbegin();
			seg.apply(tmp,i,i-tmp);
			t.insert(i);
		}
	}

    ll tmp=*t.rbegin();
	seg.apply(tmp,n,n-tmp);
	t.insert(n);

	while(q--){
		ll type;
		cin>>type;
		if(type==1){
			ll i;
			char x;
			cin>>i>>x;
			i--;

			s[i]=x;
			if(i!=0){
				if(s[i]==s[i-1])t.erase(i);
				else t.insert(i);

				auto it=t.upper_bound(i);
				auto it2=it;
				it--;
				ll l=*it,r=*it2;
				seg.apply(l,r,r-l);

				it=t.lower_bound(i);
				it2=it;
				it--;
				l=*it,r=*it2;
				seg.apply(l,r,r-l);
			}
			if(i+1!=n){
				if(s[i+1]==s[i])t.erase(i+1);
				else t.insert(i+1);

				auto it=t.upper_bound(i+1);
				auto it2=it;
				it--;
				ll l=*it,r=*it2;
				seg.apply(l,r,r-l);

				it=t.lower_bound(i+1);
				it2=it;
				it--;
				l=*it,r=*it2;
				seg.apply(l,r,r-l);
			}
		}else{
			ll l,r;
			cin>>l>>r;
			l--;
			auto itl=t.lower_bound(l);
			auto itr=t.upper_bound(r);
			itr--;

			ll il=min(*itl,r);
			ll ir=max(l,*itr);
			ll ans=max(il-l,r-ir);
			if(il<ir){
				ans=max(ans,seg.prod(il,ir));
			}
			cout<<ans<<"\n";
		}
	}
}