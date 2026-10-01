// # pragma GCC target("avx2")
// # pragma GCC optimize("O3")
// # pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;
#define ll int
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
#include<atcoder/segtree>

ll op(ll a,ll b){return max(a,b);}
ll e(){return 0;}
//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	//k以下
	vl a(n);
	rep(i,n)cin>>a[i];
	vl b=a;
	sort(b.begin(),b.end());

	vl v(n,0);
	atcoder::segtree<ll, op, e> seg(v);
	ll fans=1;
	rep(i,n){
		ll tmp=0;
		ll ans=0;
		rrep(j,30){
			if((1LL<<j)&k){
				ll checkleft = tmp;
				if(a[i]&(1LL<<j))checkleft+=(1LL<<j);
				ll checkright=checkleft+(1LL<<j)-1;

				ll left=lower_bound(b.begin(),b.end(),checkleft)-b.begin();
				ll right=upper_bound(b.begin(),b.end(),checkright)-b.begin()-1;

				if(left<=right){
					ans=max(seg.prod(left,right+1),ans);
				}

				//残りは0にしなきゃいけない
				if(!(a[i]&(1LL<<j)))tmp+=(1LL<<j);
			}else{
				//0にしなきゃいけない
				if(a[i]&(1LL<<j))tmp+=(1LL<<j);
			}
		}
		ll left=lower_bound(b.begin(),b.end(),tmp)-b.begin();
		ll right=upper_bound(b.begin(),b.end(),tmp)-b.begin()-1;
		if(left<=right){
			ans=max(seg.prod(left,right+1),ans);
		}
		ans++;
		ll ind=lower_bound(b.begin(),b.end(),a[i])-b.begin();
		seg.set(ind,ans);
		fans=max(ans,fans);
	}
	cout<<fans<<endl;
	return 0;
}
