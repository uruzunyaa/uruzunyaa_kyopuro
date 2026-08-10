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



//xor基底を求める、確認する。
struct XorBasis {
	//基底のリスト
    vl basis;

	//xを追加
    void add(ll x) {
        for (auto b : basis) {
            x=min(x,x^b);
        }
        if (x != 0) {
            basis.push_back(x);
		}
    }

    //xが含まれているか確認
	bool check(ll x){
       for (auto b : basis) {
            x=min(x,x^b);
        }
        return x==0;
    }
};


//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl v(n),w(n);
	rep(i,n){
		cin>>v[i]>>w[i];
	}
	vl t(m);
	rep(i,m)cin>>t[i];

	ll ans=0;
	rep(b,1LL<<n){
		vl a;
		rep(i,n){
			if(b&(1LL<<i))a.push_back(v[i]);
			else a.push_back(w[i]);
		}
		XorBasis xb;
		rep(i,n)xb.add(a[i]);

		bool f=true;
		rep(i,m){
			if(!xb.check(t[i]))f=false;
		}
		if(f)ans++;
	}
	cout<<ans<<endl;
	return 0;
}
