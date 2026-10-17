//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

#include<atcoder/lazysegtree>

struct S{
    long long value;
    int size;
};
using F = long long;

S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){ return {x.value + f*x.size, x.size}; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

void euler_tour(vvl &g,ll node,ll mae,vector<pair<ll,ll>> & ans,ll & cnt){
	ans[node].first=cnt;
	cnt++;
	for(auto val:g[node]){
		if(val==mae)continue;
		euler_tour(g,val,node,ans,cnt);
	}
	ans[node].second=cnt;
	return;
}

int main(){
	ll n;
	cin>>n;
	vvl g(n);
	vl aa,bb;
	rep(i,n-1){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		g[a].push_back(b);
		g[b].push_back(a);
		aa.push_back(a);
		bb.push_back(b);
	}
	vector<pair<ll,ll>> kiroku(n);
	ll tmp=0;
	euler_tour(g,0,-1,kiroku,tmp);


	ll allsums=0;
    vector<S> v(n,{0,1});
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	
	rep(i,n-1){
		ll a=aa[i];
		ll b=bb[i];
		ll c=i+1;
		if(kiroku[a].second-kiroku[a].first<kiroku[b].second-kiroku[b].first){
			swap(a,b);
		}
		//aが親
		ll bcnt=kiroku[b].second-kiroku[b].first;
		if(bcnt>n-bcnt){
			seg.apply(kiroku[b].first,kiroku[b].second,c);
		}else{
			allsums+=c;
			seg.apply(kiroku[b].first,kiroku[b].second,-c);
		}
	}
	rep(i,n)cout<<allsums+seg.get(kiroku[i].first).value<<" ";
	cout<<endl;
}
