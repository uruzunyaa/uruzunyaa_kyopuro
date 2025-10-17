#include <bits/stdc++.h>
using namespace std;
#define ALL(v) v.begin(),v.end()
using ll = long long;

int M = 100;
vector<ll> g(M+1);

ll f(ll x) {
	if (x % 8 == 7) {
		if (x <= M) {
			return g[x];
		} else {
			return f(x / 8);
		}
	} else if (x%8==1 || x%8==5) {
		return x/4;
	} else if (x%8==3) {
		return x/8;
	} else {
		return x/2;
	}
}

int main() {
	int M = 1000;
	g.resize(M+1);
	g[1] = 0;
	for (int i = 2; i <= M; ++i) {
		vector<int> v;
		for (int j = (i+1)/2; j < i; ++j) {
			v.push_back(g[j]);
		}
		sort(ALL(v));
		v.erase(unique(ALL(v)), v.end());
		int mex = 0;
		while (mex < v.size() && v[mex]==mex) ++mex;
		g[i] = mex;
		// if (i%8==5) cerr << i << " " << g[i] << endl;
	}

	int T;
	cin >> T;
	while (T--) {
		ll H,W;
		cin >> H >> W;
		ll gH = f(H), gW = f(W);
		cout << (((gH ^ gW) == 0) ? "Second" : "First") << endl;
	}
}