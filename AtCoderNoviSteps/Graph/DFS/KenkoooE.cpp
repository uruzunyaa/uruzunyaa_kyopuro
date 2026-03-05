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

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

vector<vector<pair<ll,ll>>> g;
vl number;
bool dfs(ll node,ll mae,ll num){
	if(number[node]!=-1){
		if(num==number[node])return true;
		else return false;
	}
	number[node]=num;
	for(auto val:g[node]){
		if(val.first==mae)continue;
		if(!dfs(val.first,node,val.second-num))return false;
	}
	return true;
}

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	g=vector<vector<pair<ll,ll>>>(n*2);
	number=vl(n*2,-1);
	rep(i,m){
		ll a,b,c;
		cin>>a>>b>>c;
		a--,b--;
		g[a].push_back({n+b,c});
		g[b].push_back({n+a,c});
		g[a+n].push_back({b,c});
		g[b+n].push_back({a,c});
	}

	if(!dfs(0,-1,0)){
		cout<<0<<endl;
		return 0;
	}

	ll mn=1;
	ll mx=inf;
	rep(i,n){
		if(number[i]!=-1&&number[i+n]!=-1){
			ll tmp=number[i+n]-number[i];
			if(tmp%2!=0){
				cout<<0<<endl;
				return 0;
			}
			tmp/=2;
			mn=max(mn,tmp);
			mx=min(mx,tmp);
		}
		if(number[i]!=-1)mn=max(mn,-number[i]+1);
		if(number[i+n]!=-1)mx=min(mx,number[i+n]-1);
	}

	cout<<max(0LL,mx-mn+1)<<endl;
	return 0;
}
