#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; i++)
#define rrep(i, n) for(ll i = n-1; i >= 0; i--)
 constexpr ll INF = 9009009009009009009LL;
#define vl vector<ll>


int main(){
    string p, q; cin >> p >> q;
	p = 'S' + p + 'G';
	q = 'S' + q + 'G';

	vector<vector<ll>> p_prevmap(p.size(), vector<ll>(2));
    vector<vector<ll>> q_prevmap(q.size(), vector<ll>(2));
    ll prev0 = 0, prev1 = 0;
    rep(i,p.size()) {
        p_prevmap[i][0] = prev0;
        p_prevmap[i][1] = prev1;
        if (p[i] == '0') prev0 = i;
        else prev1 = i;
    }

    prev0 = 0, prev1 = 0;
    rep(i,q.size()) {
        q_prevmap[i][0] = prev0;
        q_prevmap[i][1] = prev1;
        if (q[i] == '0') prev0 = i;
        else prev1 = i;
    }

    vector<vector<ll>> dp(p.size(),vl(q.size(),INF));
	dp[p.size()-1][q.size()-1]=0;
	rrep(i,p.size()){
		rrep(j,q.size()){
			if(dp[i][j]==INF)continue;
			rep(k,2){
				ll ni=p_prevmap[i][k];
				ll nj=q_prevmap[j][k];
				dp[ni][nj]=min(dp[i][j]+1,dp[ni][nj]);
			}
		}
	}


	vector<vector<ll>> p_nextmap(p.size(), vector<ll>(2));
    vector<vector<ll>> q_nextmap(q.size(), vector<ll>(2));
    prev0 = p.size() - 1, prev1 = p.size() - 1;
    for (ll i = p.size() - 1; i >= 0; --i) {
        p_nextmap[i][0] = prev0;
        p_nextmap[i][1] = prev1;
        if (p[i] == '0') prev0 = i;
        else prev1 = i;
    }
    prev0 = q.size() - 1, prev1 = q.size() - 1;
    for (ll i = q.size() - 1; i >= 0; --i) {
        q_nextmap[i][0] = prev0;
        q_nextmap[i][1] = prev1;
        if (q[i] == '0') prev0 = i;
        else prev1 = i;
    }
	ll i=0,j=0;
	while(i!=p.size()-1||j!=q.size()-1){
		//0を選んだ場合
		ll ni=p_nextmap[i][0];
		ll nj=q_nextmap[j][0];
		cout<<ni<<" "<<nj<<" "<<dp[ni][nj]<<endl;
		if(dp[ni][nj]==dp[i][j]-1){
			cout<<0;
			i=ni;
			j=nj;
			continue;
		}
		ni=p_nextmap[i][1];
		nj=q_nextmap[j][1];
		cout<<1;
		i=ni;
		j=nj;
	}
	cout<<endl;

	// rep(i,p.size()){
	// 	rep(j,q.size()){
	// 		cout<<dp[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
}