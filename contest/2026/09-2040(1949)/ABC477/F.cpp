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

//メイン
int main(){
	ll n,m,q;
	cin>>n>>m>>q;
	vl l(n),r(n);
	rep(i,n)cin>>l[i]>>r[i],l[i]--;
	vvl abcd;
	vvl list;
	rep(i,q){
		vl tabcd;
		rep(j,4){
			ll tmp;
			cin>>tmp;
			if(j%2==0)tmp--;
			tabcd.push_back(tmp);
		}
		abcd.push_back({tabcd});
		list.push_back({tabcd[0],tabcd[2],tabcd[3]});
		list.push_back({tabcd[1],tabcd[2],tabcd[3]});
	}
	sort(list.begin(),list.end());

	map<vl,ll> mp;
	std::vector<S> v(m,{0,1});
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	
	ll ind=0;
	for(auto val:list){
		while(val[0]>ind){
			seg.apply(l[ind],r[ind],1LL);
			ind++;
		}
		mp[val]=seg.prod(val[1],val[2]).value;
	}

	rep(i,q){
		vl tabcd=abcd[i];
		vl left={tabcd[0],tabcd[2],tabcd[3]};
		vl right={tabcd[1],tabcd[2],tabcd[3]};

		cout<<mp[right]-mp[left]<<endl;
	}

	return 0;
}
