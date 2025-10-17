// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#include<atcoder/all>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#ifdef DEBUG
#include "cpp-dump/dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#endif
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
int dx[4] = {1, 0, -1, 0}; int dy[4] = {0, 1, 0, -1};


ll solve(){

	ll n,a,b,d;

	cin >> n;
	if(!n)return 1;
	cin >> a >> b >> d;

	vector<pair<ll, ll>> XY(n);
	vector<vector<ll>> grid(103, vector<ll>(103,0));
	
	for (ll i = 0; i < n; ++i) {
		ll x,y;
		cin >> x >> y;
		XY[i] = {x,y};
		grid[x][y] = 1;
	}

	ll now_x = a;
	ll now_y = b;
	ll now_muki = 0;
	ll loop_count = -1;
	ll rem = -1;
	// (向き x y): 何回目
	map<array<ll, 3>, ll> memo;
	for (ll i = 0; i < d; ++i) {
		dump(now_muki, i, now_x, now_y);
		if (memo[{now_muki,now_x, now_y}] > 0) {
			loop_count = i - memo[{now_muki, now_x, now_y}];
			rem = (d-i) % loop_count;
			break;
		}

		// memo[{now_muki, now_x,now_y}] = i;

		// if (now_x > 100 || now_y > 100 || now_x < 0 || now_y < 0) {
		// 	now_x += dx[now_muki]*(d-i);
		// 	now_y += dy[now_muki]*(d-i);
		// 	cout << now_x << ' ' << now_y << endl;
		// 	return 0;
		// }

		ll nx = now_x + dx[now_muki];
		ll ny = now_y + dy[now_muki];

		if (nx > 100 || ny > 100 || nx < 0 || ny < 0) {
			now_x += dx[now_muki]*(d-i);
			now_y += dy[now_muki]*(d-i);
			cout << now_x << ' ' << now_y << endl;
			return 0;
		}

		if (grid[nx][ny] == 1) {
			now_muki = (now_muki+1) % 4;
			--i;
			continue;
		}

		memo[{now_muki, now_x,now_y}] = i;

		now_x = nx, now_y = ny;
	}

	if (loop_count == -1) {
		cout << now_x << ' ' << now_y << endl;
		return 0;
	}

	assert(loop_count != -1);


	assert(rem != -1);
	for (ll i = 0; i < rem; ++i) {

		ll nx = now_x + dx[now_muki];
		ll ny = now_y + dy[now_muki];

		if (grid[nx][ny] == 1) {
			now_muki = (now_muki+1) % 4;
			--i;
			continue;
		}
		now_x = nx, now_y = ny;
	}

	cout << now_x << ' ' << now_y << endl;

	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}