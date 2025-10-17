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

int dx[4] {1, 0, -1, 0};
int dy[4] {0, 1, 0, -1};

int main() {
	ll h, w;
	cin >> h >> w;

	vector<string> grid(h);
	vector<P> lake;
	rep(i, h){
		cin >> grid[i];
		rep(j, w){
			if(grid[i][j] == '#') lake.push_back({i, j});
		}
	}

	ll ans = 0;
	rep(i, lake.size()) {
		vector<vector<ll>> done(h, vector<ll>(w, 0));
		queue<P> q;
		q.push(lake.front());
		done[lake.front().first][lake.front().second] = 1;

		ll connectionCnt = 0;
		while(!q.empty()) {
			P pos = q.front(); q.pop();
			connectionCnt++;

			rep(j, 4){
				int nx = pos.second + dx[j];
				int ny = pos.first + dy[j];
				if (nx < 0 || w <= nx || ny < 0 || h <= ny || grid[ny][nx] == '.' || done[ny][nx]) continue;
				if (ny == lake[i].first && nx == lake[i].second) continue;
				q.push({ny, nx});
				done[ny][nx] = 1;
			}
		}

		if (connectionCnt >= lake.size() - 1) ans++;
	}

	cout << ans + h * w - lake.size() << endl;

	return 0;
}
