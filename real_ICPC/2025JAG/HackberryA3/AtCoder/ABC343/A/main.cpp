#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using P = pair<int, int>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i < (b); ++i)

int main() {
	int a, b;
	cin >> a >> b;

	rep(i, 10)
	{
		if(i != a + b)
		{
			cout << i << endl;
			return 0;
		}
	}

	return 0;
}