//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

struct Node{
	ll to,cost;
};
//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	k++;
	vector<vector<Node>> g(n);

	
	
	
	rep(i,n)rep(j,n){
		ll c;
		cin>>c;
		g[i].push_back({j,c});
		g[j].push_back({i,c});
	}
	//dj[i][j]=頂点iのbitjと連結するための最小コスト
	vector<vvl> dj(n,vvl(n,vl(1<<k,inf)));
	
	//何も含まない物は0で初期化。
	
	rep(kore,n){
		rep(i,n)dj[kore][i][0]=0;
	
	//自分自身が既に主要都市である場合も0で初期化。
	rep(i,k-1)dj[kore][i][1<<i]=0;
	dj[kore][kore][1<<(k-1)]=0;


	loop(bit,1,(1<<k)-1){
		// {cost,i}で保管
		priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
		rep(i,n){
			//bitの部分列を対象に遷移を行う(3^ndp)
			ll tmp =bit;
			while(1){
				dj[kore][i][bit]=min(dj[kore][i][bit],dj[kore][i][bit-tmp]+dj[kore][i][tmp]);
				if(tmp==0)break;
				tmp = (bit & (tmp-1));
			}
			pq.push({dj[kore][i][bit],i});
		}
		//これでbit0からの遷移だけを考えれば良くなった。
		while(!pq.empty()){
			ll from=pq.top().second;
			ll cost=pq.top().first;
			pq.pop();
			if(dj[kore][from][bit]!=cost)continue;

			//コストでダイクストラ
			rep(i,g[from].size()){
				//更新が起きないならスキップ
				if(dj[kore][g[from][i].to][bit]<=cost+g[from][i].cost)continue;
				dj[kore][g[from][i].to][bit]=cost+g[from][i].cost;
				pq.push({dj[kore][g[from][i].to][bit],g[from][i].to});
			}
		}
	}
	}
	ll q;
	cin>>q;
	while(q--){
		ll s,t;
		cin>>s>>t;
		s--,t--;
		cout<<dj[s][t][(1<<k)-1]<<endl;
	}
	//vvdbg(dj);
	return 0;
}
