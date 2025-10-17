#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//座標圧縮した結果を求める
vl compression(vl & a){
	vl b=a;
	sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
 
    vl ans(a.size());
    for (int i = 0; i < a.size(); ++i) {
        ans[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

	return ans;
}

int main() {
    ll n;
    cin>>n;
    vl a(n);
    rep(i,n)cin>>a[i];
    vl ans=compression(a);
    rep(i,n) cout << ans[i] << endl;
}