#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)

int main() {
    ll h, w;
    cin >> h >> w;
    vector<string> c(2 * h + 1);
    vector<vector<ll>> G(h * w);
    rep(i, 2 * h + 1){
        cin >> c[i];
    }
    rep(i, h){
        rep(j, w){
            if(c[i * 2 + 2][j * 2 + 1] == '.'){
                G[w * i + j].push_back(w * i + j + w);
                G[w * i + j + w].push_back(w * i + j);
            }
            if(c[i * 2 + 1][j * 2 + 2] == '.'){
                G[w * i + j].push_back(w * i + j + 1);
                G[w * i + j + 1].push_back(w * i + j);
            }
        }
    }
    // rep(i, h * w){
    //     rep(j, G[i].size()){
    //         cout << "頂点" << i << "から" << G[i][j] <<"への辺\n";
    //     }
    // }
	

    vector<ll> dist_s(h * w, -1);
    vector<ll> dist_g(h * w, -1);
    queue<ll> q;

    q.push(0);
    dist_s[0] = 1;
    while(!q.empty()){
        ll now = q.front();
        q.pop();
        // 0 1 2
        // 3 4 5 
        for(ll next : G[now]){
            if(dist_s[next] == -1){
                dist_s[next] = dist_s[now] + 1;
                q.push(next);
            }
        }
    }

    dist_g[h * w - 1] = 1;
    q.push(h * w - 1);
    while(!q.empty()){
        ll now = q.front();
        q.pop();
        // 0 1 2
        // 3 4 5 
        for(ll next : G[now]){
            if(dist_g[next] == -1){
                dist_g[next] = dist_g[now] + 1;
                q.push(next);
            }
        }
    }
    vector<vector<ll>> froms(h, vector<ll>(w)), fromg(h, vector<ll>(w));
    rep(i, dist_s.size()){
        froms[i / w][i % w] = dist_s[i];
    }
    rep(i, dist_g.size()){
        fromg[i / w][i % w] = dist_g[i];
    }

    // froms[i][j] = sからの距離
	ll ans=fromg[0][0];
	//yoko
	rep(i,h){
		rep(j,w-1){
			if(c[i * 2 + 1][j * 2 + 2] == '.')continue;
			if(froms[i][j]+fromg[i][j+1]==fromg[i][j]+froms[i][j+1])continue;
			ll tmp=min(froms[i][j]+fromg[i][j+1],fromg[i][j]+froms[i][j+1]);
			ans=max(tmp,ans);
		}
	}
	rep(i,h-1){
		rep(j,w){
			if(c[i * 2 + 2][j * 2 + 1] == '.')continue;
            if(froms[i][j]+fromg[i+1][j] == fromg[i][j]+froms[i+1][j])continue;
			ll tmp=min(froms[i][j]+fromg[i+1][j],fromg[i][j]+froms[i+1][j]);
			ans=max(tmp,ans);
		}
	}

	cout<<ans<<endl;

}