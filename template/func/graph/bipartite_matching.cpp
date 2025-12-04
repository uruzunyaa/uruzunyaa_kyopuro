#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//左側のノード数,右側のノード数,マッチング出来る物のリストを受け取り
//最大2部マッチングを返す
//計算量:O(VE)
ll bipartite_matching(ll mxa,ll mxb,vector<pair<ll,ll>> ok){
	// 隣接リスト (左側 -> 右側)
    vvl g(mxa);
    for(auto &e : ok){
        ll a = e.first;
        ll b = e.second;
        g[a].push_back(b);
    }

    // 右側の各頂点がどの左頂点にマッチしているか (-1:未マッチ)
    vl matchR(mxb, -1);

    // 増加路探索のDFS,既にマッチ済みを付け替えれるなら付け替えながら
    auto dfs = [&](auto&& self, ll v, vl &used) -> bool {
        for(ll u : g[v]){
            if(used[u]) continue;
            used[u] = 1;
            if(matchR[u] == -1 || self(self, matchR[u], used)){
                matchR[u] = v;
                return true;
            }
        }
        return false;
    };

    ll ret = 0;
    for(ll v = 0; v < mxa; v++){
        vl used(mxb, 0);
        if(dfs(dfs, v, used)) ret++;
    }
    return ret;
}

int main(){
	
	return 0;
}
