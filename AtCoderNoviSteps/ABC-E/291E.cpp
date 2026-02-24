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

//トポロジカルソート順の中の1つを返す(DAGでない時、サイクル以外しか返ってこない)
vl topological_sort(vvl g){
	ll n=g.size();
	vl in(n,0);
	queue<ll> zero;
	rep(i,n){
		for(auto val:g[i]){
			in[val]++;
		}
	}
	rep(i,n){
		if(in[i]==0)zero.push(i);
	}
	vl ans;
	while(!zero.empty()){
		ll node=zero.front();
		ans.push_back(node);
		zero.pop();
		for(auto val:g[node]){
			in[val]--;
			if(in[val]==0)zero.push(val);
		}
	}
	return ans;
}

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	
	vvl g(n);
	set<pair<ll,ll>> st;
	rep(i,m){
		ll x,y;
		cin>>x>>y;
		x--,y--;
		g[x].push_back(y);
		st.insert({x,y});
	}

	vl tps=topological_sort(g);
	vl ans(n);
	rep(i,n-1){
		if(!st.count({tps[i],tps[i+1]})){
			cout<<"No"<<endl;
			return 0;
		}
		ans[tps[i]]=i+1;
	}
	ans[tps.back()]=n;
	cout<<"Yes"<<endl;
	vdbg(ans);

	return 0;
}
