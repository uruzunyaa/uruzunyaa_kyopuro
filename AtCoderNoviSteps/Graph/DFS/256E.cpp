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


vl e;
vl c;
vl visited;
//{コスト,閉路内か}
pair<ll,bool> dfs(ll node){
	if(visited[node]==1)return {0,false};
	if(visited[node]==0){
		visited[node]=1;
		return {c[node],true};
	}
	visited[node]=0;
	auto ans=dfs(e[node]);
	if(visited[node]==1){
		ans.second=false;
	}

	if(ans.second==true){
		ans.first=min(ans.first,c[node]);
	}
	visited[node]=1;
	return ans;
}

//メイン
int main(){
	ll n;
	cin>>n;
	visited=vl(n,-1);
	rep(i,n){
		ll tmp;
		cin>>tmp;
		tmp--;
		e.push_back(tmp);
	}
	rep(i,n){
		ll tmp;
		cin>>tmp;
		c.push_back(tmp);
	}

	ll ans=0;
	rep(i,n)ans+=dfs(i).first;
	cout<<ans<<endl;
	
	return 0;
}
