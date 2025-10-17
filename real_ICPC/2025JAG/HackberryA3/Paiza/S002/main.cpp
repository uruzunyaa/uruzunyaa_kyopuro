#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
const ll INF = 1001001001001001001LL;

template <class T>
inline bool chmax(T &a, const T &b) {
	if (a < b) {
		a = b;
		return true;
	}
	return false;
}
template <class T>
inline bool chmin(T &a, const T &b) {
	if (a > b) {
		a = b;
		return true;
	}
	return false;
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
	ll m, n; cin >> m >> n;

	vvll g(n, vll(m));
	P start, goal;
	rep(i, n) rep(j, m) {
		char c; cin >> c;
		if(c == 's') {
			start = {i, j};
			g[i][j] = 0;
		}
		if(c == 'g') {
			goal = {i, j};
			g[i][j] = 0;
		}

		g[i][j] = c - '0';
	}

	vvll dist(n, vll(m, INF));
	queue<P> q;
	q.push(start);
	dist[start.first][start.second] = 0;
	while(!q.empty()) {
		auto [y, x] = q.front(); q.pop();

		rep(i, 4){
			ll ny = y + dy[i];
			ll nx = x + dx[i];

			if(ny < 0 || ny >= n || nx < 0 || nx >= m || g[ny][nx] == 1) continue;
			if(dist[ny][nx] != INF) continue;

			dist[ny][nx] = dist[y][x] + 1;
			q.push({ny, nx});
		}
	}

	if(dist[goal.first][goal.second] == INF) cout << "Fail" << endl;
	else cout << dist[goal.first][goal.second] << endl;

	return 0;
}
