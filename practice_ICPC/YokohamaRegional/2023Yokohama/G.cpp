#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= (ll)b; ++i)

int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};

int main(){
	ll n;
	cin>>n;
	double tmp=7.0/6.0;
	double ans=1;
	rep(i,n)ans*=tmp;
	cout<<ans<<endl;
}