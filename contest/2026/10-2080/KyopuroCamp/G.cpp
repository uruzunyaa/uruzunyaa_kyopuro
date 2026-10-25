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

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
#include<atcoder/lazysegtree>

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

//メイン
//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro
int main(){
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	ll n;
	cin>>n;
	vvvl lrduv(200000);
	rep(i,n){
		ll l,r,d,u,v;
		cin>>l>>r>>d>>u>>v;
		l--,r--,d--,u--;
		lrduv[l].push_back({d,u,v});
		lrduv[r].push_back({d,u,-v});
	}
	vl v(200000,0);
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	ll q;
	cin>>q;
	vvl query;
	rep(i,q){
		ll x,y;
		cin>>x>>y;
		x--,y--;
		query.push_back({x,y,i});
	}

	sort(query.begin(),query.end());

	vl ans(q);

	ll qi=0;
	rep(i,200000){
		for(auto val:lrduv[i]){
			seg.apply(val[0],val[1],val[2]);
		}
		while(qi<q&&query[qi][0]==i){
			ll tmp=seg.get(query[qi][1]);
			if(tmp==0)tmp--;
			ans[query[qi][2]]=tmp;
			qi++;
		}
	}

	rep(i,q){
		cout<<ans[i]<<"\n";
	}
	
	return 0;
}
