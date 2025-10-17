// #BFS
// n個の数列aが与えられるので、回文にするために必要な最小操作回数を求めよ
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

int main()
{
	int n;
	cin >> n;
	vi a(n);
	rep(i, n) cin >> a[i];

	vvi g(2 * 1e5 + 1);
	rep(i, n){
		if(a[i] == a[n - i - 1]) continue;
		g[a[i]].push_back(a[n - i - 1]);
	}

	int ans = 0;
	unordered_set<int> unvisited(n);
	rep(i, n) unvisited.insert(a[i]);
	while(unvisited.size())
	{
		int start = *unvisited.begin();
		unvisited.erase(start);

		queue<int> q;
		q.push(start);

		while(q.size())
		{
			int v = q.front();
			q.pop();
			for(auto u : g[v])
			{
				if(unvisited.count(u))
				{
					unvisited.erase(u);
					q.push(u);
					ans++;
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}
