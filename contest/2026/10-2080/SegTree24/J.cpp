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

struct S{
    long long value;
    long long size;
};
using F = long long;

S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){
    if(f==1)x.value=x.size-x.value;
    return x;
}
F composition(F f, F g){ return (f^g); }
F id(){ return 0; }

int main(){
    ll n;
    cin>>n;
    vl t(n),l(n),r(n);
    map<ll,ll> mp;
    rep(i,n){
        cin>>t[i]>>l[i]>>r[i];
        l[i]--;
        mp[l[i]]++;
        mp[r[i]]++;
    }
    ll cnt=-1;
    vl zisho;
    for(auto &val:mp){
        cnt++;
        val.second=cnt;
        zisho.push_back(val.first);
    }
    vector<S> v(cnt);
    rep(i,cnt){
        v[i]={0,zisho[i+1]-zisho[i]};
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
    rep(i,n){
        if(t[i]==1){
            seg.apply(mp[l[i]],mp[r[i]],1);
        }else{
            cout<<seg.prod(mp[l[i]],mp[r[i]]).value<<endl;
        }
    }
	
}