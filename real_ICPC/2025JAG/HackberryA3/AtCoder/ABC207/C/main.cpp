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
	int N;
	cin >> N;

	vector<pair<double,double>> LR(N);
	int ans = 0;
	rep(i, N)
	{
		int t;
		cin >> t;
		double l, r;
		cin >> l >> r;

		if (t == 2)
			r-=0.5;
		if (t == 3)
			l+=0.5;
		if (t == 4)
		{
			l+=0.5;
			r-=0.5;
		}

		rep(j, i){
			if (max(LR[j].first, l) <= min(LR[j].second, r))
				ans++;
		}
		LR[i] = (pair<double,double>(l, r));
	}

	/*
	1 2
	2 2.9
	2.1 4
	*/

	cout << ans << endl;

	return 0;
}