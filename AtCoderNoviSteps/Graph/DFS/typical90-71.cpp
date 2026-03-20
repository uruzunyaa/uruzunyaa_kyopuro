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


vvl ans;

ll n,k;
void dfs(vl & root,set<ll> & ok,ll node,vvl & g,vl & indeg){
	if(k==0)return;
	root.push_back(node+1);
	if(root.size()==n){
		ans.push_back(root);
		root.pop_back();
		k--;
		return;
	}
	ok.erase(node);
	for(auto nxt : g[node]){
		indeg[nxt]--;
		if(indeg[nxt]==0)ok.insert(nxt);
	}
	
	ll cnt=k;
	vl kouho;
	for(auto val:ok){
		if(cnt==0)break;
		kouho.push_back(val);
		cnt--;
	}

	for(auto val:kouho){
		dfs(root,ok,val,g,indeg);
	}

	for(auto nxt : g[node]){
		indeg[nxt]++;
		ok.erase(nxt);
	}

	root.pop_back();
	ok.insert(node);
	return;
}

//メイン
int main(){
	ll m;
	cin>>n>>m>>k;
	vvl g(n);
	vl indeg(n,0);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		g[a].push_back(b);
		indeg[b]++;
	}
	vl tps=topological_sort(g);
	if(tps.size()!=n){
		cout<<-1<<endl;
		return 0;
	}

	set<ll> ok;
	rep(i,n){
		if(indeg[i]==0)ok.insert(i);
	}

	vl root;
	rep(i,n){
		if(!ok.count(i))continue;
		dfs(root,ok,i,g,indeg);
	}

	if(k!=0){
		cout<<-1<<endl;
	}else{
		vvdbg(ans);
	}
	
	return 0;
}
