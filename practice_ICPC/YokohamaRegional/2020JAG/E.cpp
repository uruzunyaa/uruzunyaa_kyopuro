#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000000000000LL

vl dx={0,0,1,-1};
vl dy={1,-1,0,0};

struct path{
	ll node;
	ll cost;
};

int main(){
    ll h,w;
	cin>>h>>w;
	vvl a(h,vl(w));
	vvl b=a;
	rep(i,h)rep(j,w)cin>>a[i][j];
	rep(i,h)rep(j,w)cin>>b[i][j];

	vector<vector<path>> g(h*w);

	rep(i,h)rep(j,w){
		rep(d,4){
			ll nx=i+dx[d];
			ll ny=j+dy[d];
			if(nx<0||h<=nx||ny<0||w<=ny){
				continue;
			}

			ll ijtmp=i*w+j;
			ll nxytmp=nx*w+ny;
			g[ijtmp].push_back({nxytmp,-a[i][j]});
			g[nxytmp].push_back({ijtmp,b[i][j]});

			//cout<<ijtmp<<" "<<nxytmp<<" "<<-a[i][j]<<endl;
		}
	}

	vl dist(h*w,inf);

	dist[0]=500000000;
	bool ansok;
	rep(z,h*w*2){
		ansok=true;
		rep(i,h*w){
			rep(j,g[i].size()){
				ll next=g[i][j].node;
				ll cost=g[i][j].cost;
				if(dist[next]>dist[i]+cost){
					dist[next]=dist[i]+cost;
					ansok=false;
				}
			}
		}
	}


	if(!ansok){
		cout<<-1<<endl;
		return 0;
	}


	rep(i,h*w){
		cout<<dist[i]<<" ";
		if(i%w==w-1)cout<<endl;
	}
    return 0;
}