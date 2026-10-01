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


//グラフgを受け取り、頂点0から頂点n-1への最大流を求める
//pairの順序は{行き先,流量}
//計算量:O(VEE)
ll max_flow(vector<vector<pair<ll,ll>>> &g){
    ll n = (ll)g.size();
    // cap[u][v] : u -> v の残余容量
    vvl cap(n, vl(n, 0));
    // 残余グラフの隣接リスト（無向風に持っておく）
    vector<vector<ll>> adj(n);

    // 入力から容量行列と隣接リストを構築
    for(ll u = 0; u < n; u++){
        for(auto &e : g[u]){
            ll v = e.first;
            ll c = e.second;
            if(c < 0) continue; // 負容量は無視（普通は来ない前提）
            if(cap[u][v] == 0){
                // 初めて見る辺なら、残余グラフの隣接にも登録
                adj[u].push_back(v);
                adj[v].push_back(u); // 逆辺（残余用）も登録
            }
            cap[u][v] += c; // 多重辺をまとめておく
        }
    }

    ll flow = 0;
    const ll s = 0;
    const ll t = n - 1;

    while(true){
        // BFS で増加路探索
        vl parent(n, -1);   // parent[v] : 増加路上で v に来る直前の頂点
        vl mincap(n, 0);    // ここまでのパスのボトルネック容量
        queue<ll> que;

        parent[s] = -2;     // s の親は特別な値
        mincap[s] = inf;    // s からのボトルネックはとりあえず無限大
        que.push(s);

        while(!que.empty() && parent[t] == -1){
            ll v = que.front(); que.pop();
            for(ll to : adj[v]){
                if(parent[to] == -1 && cap[v][to] > 0){
                    parent[to] = v;
                    mincap[to] = min(mincap[v], cap[v][to]);
                    if(to == t) break; // t に到達したら終了
                    que.push(to);
                }
            }
        }

        // t に到達できなかったらこれ以上流せない
        if(parent[t] == -1) break;

        // 見つかった増加路に流せる量
        ll add = mincap[t];
        flow += add;

        // 残余容量の更新（s から t まで親を辿って戻る）
        ll cur = t;
        while(cur != s){
            ll p = parent[cur];
            cap[p][cur] -= add;
            cap[cur][p] += add;
            cur = p;
        }
    }

    return flow;
}

ll h,w;

ll ind(ll i,ll j){
	return i*w+j+1;
}

//メイン
int main(){
	cin>>h>>w;
	//pairの順序は{行き先,流量}
	vector<vector<pair<ll,ll>>> g(h*w+2);
	vector<string> s(h);
	rep(i,h)cin>>s[i];

	ll t=h*w+1;

	rep(i,h){
		//横
		rep(j,w-1){
			if(s[i][j]=='#')continue;
			if(s[i][j+1]=='#')continue;
			ll a=ind(i,j);
			ll b=ind(i,j+1);
			g[a].push_back({b,inf});
			g[b].push_back({a,inf});
		}
	}

	rep(j,w){
		//下
		rep(i,h-1){
			if(s[i][j]=='#')continue;
			if(s[i+1][j]=='#')continue;
			ll a=ind(i,j);
			ll b=ind(i+1,j);
			g[a].push_back({b,inf});
		}
	}


	ll ans=0;
	
	rep(i,h){
		rep(j,w){
			if(s[i][j]=='#')continue;
			
			ll node=ind(i,j);
			if(s[i][j]=='+'){
				//先に一旦選んだ事にする。
				ans++;
				g[node].push_back({t,1});
			}else{
				g[0].push_back({node,1});
			}
			
		}
	}

	ans-=max_flow(g);
	cout<<ans<<endl;

	return 0;
}
