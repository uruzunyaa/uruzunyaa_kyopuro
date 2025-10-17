#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

int solve() {
	ll n;
	cin >> n;
	if(n == 0){return 1;}
	ll ans = 0;
	rep(i, n){
		rep(j, n){
			ans += (i + 1) * (j + 1);
		}
	}
	cout << ans << endl;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(solve() == 0);

    return 0;
}
