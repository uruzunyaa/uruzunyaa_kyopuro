#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

vll mach;
vector<pair<ll,ll>> x_y;
ll m;
ll dfs(ll a){
	if(a==m){
		//ここに実際にマッチングしてみる処理を書きます
		ll cnt = 0;
        const double double_inf = 1000000000;
        rep(i, mach.size()) {
            ll point1_x = x_y[i].first;
            ll point1_y = x_y[i].second;
            ll point2_x = x_y[mach[i]].first - point1_x;
            ll point2_y = x_y[mach[i]].second - point1_y;
            point1_x = 0;
            point1_y = 0;

            double angle1;
            if (point2_x == 0) angle1 = double_inf;
            else angle1 = (double)point2_y / point2_x;

            rep(j, i) {
                if (mach[i] == j) continue;
                ll point21_x = x_y[j].first;
                ll point21_y = x_y[j].second;
                ll point22_x = x_y[mach[j]].first - point21_x;
                ll point22_y = x_y[mach[j]].second - point21_y;
                point21_x = 0;
                point21_y = 0;

                double angle2;
                if (point22_x == 0) angle2 = double_inf;
                else angle2 = (double)point22_y / point22_x;

                if (angle1 == angle2) cnt++;
            }
        }
        return cnt / 4;
	}
	if(mach[a]!=INF)return dfs(a+1);

	ll ans=0;
	loop(i,a+1,m-1){
		if(mach[i]!=INF)continue;
		mach[i]=a;
		mach[a]=i;
		
		ans=max(ans,dfs(a+1));

		mach[i]=INF;
		mach[a]=INF;
	}
	return ans;
}

int main() {
    
    cin >> m;
	mach=vll(m,INF);
    x_y=vector<pair<ll,ll>>(m);
    rep(i, m){
        cin >> x_y[i].first >> x_y[i].second;
    }

	cout<<dfs(0)<<endl;
    return 0;
}