//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
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
//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


void solve(){
	ll n;
	string a,b;
	cin>>n>>a>>b;

	//両隣が合わない場合を排除
	if(a[0]!=b[0]||a[n-1]!=b[n-1]){
		cout<<-1<<endl;
		return;
	}
	
	//最初と最後に0を補って、それぞれ隣接XORを取る
	vl axor,bxor;
	axor.push_back(0);
	bxor.push_back(0);
	rep(i,n-1){
		if(a[i]==a[i+1])axor.push_back(0);
		else axor.push_back(1);

		if(b[i]==b[i+1])bxor.push_back(0);
		else bxor.push_back(1);
	}
	axor.push_back(0);
	bxor.push_back(0);

	//隣接XORの隣接XORを見て、Aの0の場所を保管する。
	vl adoublexor,bdoublexor;
	rep(i,n){
		adoublexor.push_back(axor[i]^axor[i+1]);
		bdoublexor.push_back(bxor[i]^bxor[i+1]);
	}
	set<ll> zero;
	zero.insert(inf);
	rep(i,n)if(adoublexor[i]==0)zero.insert(i);
	
	//可能な操作は0の両隣を反転させる事になっている。
	//反転させたいbitをi、iより大きい最も近い0の場所をjとして、j-iのコストで以下の操作が可能
	//i,i+1,j,j+1を反転させる。(i+1==jの時はここが打ち消し合う)
	ll ans=0;
	rep(i,n){
		if(adoublexor[i]==bdoublexor[i])continue;
		ll j=*zero.upper_bound(i);
		if(j>n-2){
			cout<<-1<<endl;
			return;
		}

		ans+=j-i;

		adoublexor[i]^=1;
		adoublexor[i+1]^=1;
		adoublexor[j]^=1;
		adoublexor[j+1]^=1;

		zero.erase(i);
		zero.erase(i+1);
		zero.erase(j);
		zero.erase(j+1);

		if(adoublexor[i]==0)zero.insert(i);
		if(adoublexor[i+1]==0)zero.insert(i+1);
		if(adoublexor[j]==0)zero.insert(j);
		if(adoublexor[j+1]==0)zero.insert(j+1);
	}
	cout<<ans<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
