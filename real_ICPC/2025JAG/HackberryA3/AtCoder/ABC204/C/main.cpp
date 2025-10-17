// #BFS
// 有向グラフが与えられるので、各頂点から到達可能な頂点の数を求める問題
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i <= (b); ++i)

int main() {
	int n, m; cin >> n >> m;
	vvi to(n);
	rep(i, m) {
		int a, b; cin >> a >> b;
		to[a - 1].push_back(b - 1);
	}

	int ans = 0;
	rep(i, n)
	{
		queue<int> q;
		vi visited(n, 0);
		q.push(i);
		visited[i] = 1;

		// cout << i << "->" << i << endl;
		++ans;

		while (q.size())
		{
			int now = q.front(); q.pop();
			for(auto next : to[now])
			{
				if(visited[next]) continue;
				visited[next] = 1;
				q.push(next);

				// cout << i << "->" << next << endl;
				++ans;
			}
		}
	}

	cout << ans << endl;

	return 0;
}
