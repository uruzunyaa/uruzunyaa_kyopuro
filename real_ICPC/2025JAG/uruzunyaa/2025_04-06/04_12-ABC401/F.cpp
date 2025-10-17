#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL

#include <atcoder/all>


//受け取ったグラフ上で、最も遠い距離の頂点を返す
ll bfs(vvl &g ,vl &dist,ll p){
	ll ans=p;
	queue<ll> bfs;
	vl kyori(g.size(),inf);
	kyori[p]=0;
	bfs.push(p);
	while(!bfs.empty()){
		ll tmp=bfs.front();
		bfs.pop();
		dist[tmp]=max(dist[tmp],kyori[tmp]);
		ans=tmp;
		rep(i,g[tmp].size()){
			if(kyori[g[tmp][i]]<=kyori[tmp]+1)continue;
			kyori[g[tmp][i]]=kyori[tmp]+1;
			bfs.push(g[tmp][i]);
		}
	}
	return ans;
}

//メイン
int main(){
	vl dummy(200001,inf);

	ll n;
	cin>>n;
	vl dist=vl(n,0);
	vvl g=vvl(n);
	rep(i,n-1){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	ll tmp=bfs(g,dummy,0);
	ll ttmp=bfs(g,dist,tmp);
	bfs(g,dist,ttmp);

	ll m;
	cin>>m;
	vl dist2=vl(m,0);
	vvl g2=vvl(m);
	rep(i,m-1){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g2[u].push_back(v);
		g2[v].push_back(u);
	}
	ll tmp2=bfs(g2,dummy,0);
	ll ttmp2=bfs(g2,dist2,tmp2);
	bfs(g2,dist2,ttmp2);



	ll mx=0;
	vl bucket1(n,0),bucket2(m,0);
	rep(i,n){
		bucket1[dist[i]]++;
		mx=max(mx,dist[i]);
	}

	rep(i,m){
		bucket2[dist2[i]]++;
		mx=max(mx,dist2[i]);
	}

	vl s=atcoder::convolution_ll(bucket1,bucket2);

	ll ans=0;
	rep(i,s.size()){
		ans+=s[i]*max(i+1,mx);
	}
	cout<<ans<<endl;
	//vdbg(dist);
	return 0;
}
