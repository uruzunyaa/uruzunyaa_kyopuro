#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define ALL(v) v.begin(),v.end()
#define sq(x) ((x)*(x))

bool f(ll sx,ll sy, ll l, ll x, ll y) {
	return l > 0 && sq(x-sx) - sq(y-sy) <= l;
}
int H,W,L;
int main() {
	cin >> H >> W >>L;

	ll ans = 0;
	{//1
		for (int x = 0; x <= L; ++x) {
			int l=0,r=2*L+1;
			while (r-l > 1) {
				int mid = (l + r) / 2;
				bool f1 = f(L,L,L,x,mid);
				(f1 ? l : r) = mid;
			}
			ans += l - L;
		}
	}
	{//2
		for (int x = 0; x <= L; ++x) {
			int l=0,r=2*L+1;
			while (abs(r-l) > 1) {
				int mid = (l + r) / 2;
				bool f1 = f(L,L,L,x,mid);
				(f1 ? l : r) = mid;
			}
			ans += l - L;
		}
	}
}