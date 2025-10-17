#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

int solve() {
	ll n;
	cin >>n;
	if(n == 0){return 1;}
	vector<ll> a(n);
	rep(i, n){
		cin >> a[i];
	}
	ll i = 1;
	while(1){
		if( a[i - 1] != i){
			cout << i << endl;
			break;
		}
		i++;
	}
    return 0;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(solve() == 0);
    return 0;
}
