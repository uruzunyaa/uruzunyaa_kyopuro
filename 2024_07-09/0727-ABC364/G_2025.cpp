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


struct Node{
	ll to,cost;
};
//Nを頂点数,Mを辺数,Kを指定頂点数として
//計算量(3^K)*N+(2^k)*M log M で
//指定頂点＋自分自身に対する最小全域木のコストを求める
//listは指定頂点のリストを指定する。
vl min_steiner_tree(vector<vector<Node>> &g,vl &list){
	
	ll n=g.size();
	ll k=list.size();

	//dj[i][j]=頂点iのbitjと連結するための最小コスト
	vvl dj(n,vl(1<<k,inf));
	
	//何も含まない物は0で初期化。
	rep(i,n)dj[i][0]=0;
	
	//自分自身が指定頂点である場合も0で初期化。
	rep(i,k)dj[list[i]][1<<i]=0;

	loop(bit,1,(1<<k)-1){
		// {cost,i}で保管
		priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
		rep(i,n){
			//bitの部分列を対象に遷移を行う(3^ndp)
			ll tmp =bit;
			while(1){
				dj[i][bit]=min(dj[i][bit],dj[i][bit-tmp]+dj[i][tmp]);
				if(tmp==0)break;
				tmp = (bit & (tmp-1));
			}
			pq.push({dj[i][bit],i});
		}
		//これでbit0からの遷移だけを考えれば良くなった。
		while(!pq.empty()){
			ll from=pq.top().second;
			ll cost=pq.top().first;
			pq.pop();
			if(dj[from][bit]!=cost)continue;

			//コストでダイクストラ
			rep(i,g[from].size()){
				//更新が起きないならスキップ
				if(dj[g[from][i].to][bit]<=cost+g[from][i].cost)continue;
				dj[g[from][i].to][bit]=cost+g[from][i].cost;
				pq.push({dj[g[from][i].to][bit],g[from][i].to});
			}
		}
	}
	vl ans;
	rep(i,n)ans.push_back(dj[i][(1<<k)-1]);
	return ans;
}

int main(){
	ll n,m,k;
	cin>>n>>m>>k;
	vector<vector<Node>> g(n);
	rep(i,m){
		ll a,b,c;
		cin>>a>>b>>c;
		a--,b--;
		g[a].push_back({b,c});
		g[b].push_back({a,c});
	}
	vl list;
	rep(i,k-1)list.push_back(i);
	vl ans=min_steiner_tree(g,list);
	loop(i,k-1,n-1){
		cout<<ans[i]<<endl;
	}
}
