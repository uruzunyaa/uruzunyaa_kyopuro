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
    ll n,q;
    cin>>n>>q;
    vl a(n);
    rep(i,n)cin>>a[i];
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
    while(q--){
        ll t,l,r;
        cin>>t>>l>>r;
        l--;
        if(t==1){
            ll x;
            cin>>x;
            seg.apply(l,r,x);
        }else{
            cout<<seg.prod(l,r)<<endl;
        }
    }
	
}