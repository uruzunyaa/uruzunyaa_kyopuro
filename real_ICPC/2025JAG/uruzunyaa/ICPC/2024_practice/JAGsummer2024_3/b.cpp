#include <bits/stdc++.h>
using namespace std;
#define ALL(v) v.begin(),v.end()
struct UF {
	int n;
	vector<int> par,rank,size;
	UF(int n) : n(n), par(n), rank(n) , size(n,1)
	{
		iota(ALL(par),0);
	}
	int root(int x) {
		if (x == par[x]) return x;
		return par[x] = root(par[x]);
	}
	bool unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (rank[x] > rank[y]) swap(x,y);
		if (rank[x] == rank[y]) rank[y]++;
		par[x] = y;
		size[y] += size[x];
		return true;
	}
	int sz(int x) {
		return size[ root(x) ];
	}
};
int H,W;
vector<string> S;
int main() {
	cin >> H >> W;
	S.resize(H);
	for (int i = 0; i < H; ++i) cin >> S[i];

	int dx[] = {-1,0,1,0,-1};
	UF uf(H*W);
	auto id = [&](int x, int y) {
		return y * W + x;
	};
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (S[i][j]=='#') continue;
			for (int k = 0; k < 4; ++k) {
				int nx = j + dx[k];
				int ny = i + dx[k+1];
				if (!(0 <= nx && nx < W && 0 <= ny && ny < H)) continue;
				if (S[ny][nx]=='#') continue;
				uf.unite(id(j,i), id(nx,ny));
			}
		}
	}
	int sx,sy;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (S[i][j]=='S') {
				sx = j;
				sy = i;
				break;
			}
		}
	}
	int sr = uf.root(id(sx,sy));
	int ans = uf.sz(id(sx,sy));
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (S[i][j]=='#') {
				vector<int> leader;
				int area = 1;
				for (int k = 0; k < 4; ++k) {
					int nx = j + dx[k];
					int ny = i + dx[k+1];
					if (!(0 <= nx && nx < W && 0 <= ny && ny < H)) continue;
					if (S[ny][nx] == '#') continue;
					int r = uf.root(id(nx,ny));
					bool ok = true;
					for (int l : leader) {
						if (l == r) {
							ok = false;
							break;
						}
					}
					if (ok) {
						leader.push_back(r);
						area += uf.sz(r);
					}
				}
				bool ok = false;
				for (int l : leader) {
					if (l == sr) {
						ok = true;
						break;
					}
				}
				if (ok) ans = max(ans, area);
			}
		}
	}
	cout << ans << endl;
}