#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define inf 4000000000000000000LL
#define mod 998244353LL

//座標圧縮した結果を求める
vl compression(vl & a){
	vl b=a;
	sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
 
    vl ans(a.size());
    for (int i = 0; i < a.size(); ++i) {
        ans[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

	return ans;
}

int main() {
    
}