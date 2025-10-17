#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
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

using PP = pair<int, P>;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

vector<vector<int> > g, dist;

int h, w;

void dijkstra(int sx, int sy) {
    dist = vector<vector<int> >(h, vector<int>(w, 1 << 30));
    dist[sx][sy] = 0;
    priority_queue<PP, vector<PP>, greater<PP> > pq;
    pq.push(PP(0, P(sx, sy)));

    while (!pq.empty()) {
        PP p = pq.top();
        pq.pop();
        int c = p.first;
        int vx = p.second.first, vy = p.second.second;

        rep (i, 4) {
            int nx, ny;
            nx = vx + dx[i], ny = vy + dy[i];
            if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
            if (dist[nx][ny] <= g[nx][ny] + c) continue;
            dist[nx][ny] = g[nx][ny] + c;
            pq.push(PP(dist[nx][ny], P(nx, ny)));
        } 
    }
}


int main() {
	ll n; cin >> n;
	h = w = n;
	vvi red(n, vi(n, 0)), blue(n, vi(n, 0));
	rep(i, n) {
		string s; cin >> s;
		rep(j, n) {
			if(s[j] == 'B') red[i][j] = 1;
			else if(s[j] == 'R') blue[i][j] = 1;
		}
	}

	g = red;
	dijkstra(0, 0);
	int red_cost = dist[n - 1][n - 1];
	g = blue;
	dijkstra(0, n - 1);
	int blue_cost = dist[n - 1][0];

	cout << (red_cost + blue_cost) << endl;

	return 0;
}
