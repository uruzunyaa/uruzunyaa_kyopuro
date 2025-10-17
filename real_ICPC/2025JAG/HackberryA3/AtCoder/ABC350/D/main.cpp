// #BFS
// 友達の友達を友達にする問題。各連結成分を完全グラフにするために必要な辺の数を求める問題
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	ll n, m; cin >> n >> m;
	vvll g(n);
	rep(i, m) {
		ll a, b; cin >> a >> b;
		--a; --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	set<ll> unvisited_group;
	set<ll> unvisited_node;
	rep(i, n) unvisited_group.insert(i);
	rep(i, n) unvisited_node.insert(i);

	ll ans = 0;
	while(unvisited_group.size()){
		ll start = *unvisited_group.begin();
		queue<ll> q;
		q.push(start);
		unvisited_group.erase(start);

		vll group;

		while(q.size()){
			ll now = q.front();
			q.pop();
			group.push_back(now);

			for(auto next : g[now]){
				if(unvisited_group.count(next)){
					unvisited_group.erase(next);
					q.push(next);
				}
			}
		}

		ll cnt = 0;
		unordered_set<ll> done;
		q.push(start);
		unvisited_node.erase(start);

		while(q.size()){
			ll now = q.front();
			q.pop();
			done.insert(now);

			ll doneCnt = done.size();
      		rep(i, g[now].size()) if(done.count(g[now][i])) --doneCnt;
			cnt += group.size() - g[now].size() - doneCnt;

			for(auto next : g[now]){
				if(unvisited_node.count(next)){
					unvisited_node.erase(next);
					q.push(next);
				}
			}
		}

		ans += cnt;
	}

	cout << ans << endl;

	return 0;
}
