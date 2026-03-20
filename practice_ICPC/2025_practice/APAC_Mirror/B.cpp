#include <bits/stdc++.h>
using namespace std;
using ll = int;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define rrep(i, n) for(ll i = n-1; i >= 0; --i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000

vvl g;
vl cost;

map<ll,vl> mp;

vl dfs(ll node){
	if(mp.count(node)){
		return mp[node];
	}
	vl ans;
	if(cost[node]!=-1){
		ans.push_back(cost[node]);
		mp[node]=ans;
		return ans;
	}
	
	deque<pair<ll,ll>> dq;
	for(auto val:g[node]){
		vl tmp=dfs(val);
		if(tmp.size()==1){
			dq.push_back({tmp[0],-1});
		}else{
			dq.push_back({tmp[0],tmp[1]});
			dq.push_back({tmp[1],tmp[0]});
		}
	}

	sort(dq.begin(),dq.end());
	deque<pair<ll,ll>> dqcopy=dq;

	set<ll> sente,gote;
	while(dq.size()>1){
		ll cnt=0;
		while(dq.size()>1){
			if(sente.count(dq.back().first)){
				dq.pop_back();
				continue;
			}
			if(cnt==1)break;
			cnt++;
			sente.insert(dq.back().second);
			dq.pop_back();
		}
		cnt=0;
		while(dq.size()>1){
			if(gote.count(dq.front().first)){
				dq.pop_front();
				continue;
			}
			if(cnt==1)break;
			cnt++;
			gote.insert(dq.front().second);
			dq.pop_front();
		}
	}
	ll senteans=dq[0].first;

	sente.clear();
	gote.clear();
	dq=dqcopy;

	while(dq.size()>1){
		ll cnt=0;
		while(dq.size()>1){
			if(gote.count(dq.front().first)){
				dq.pop_front();
				continue;
			}
			if(cnt==1)break;
			cnt++;
			gote.insert(dq.front().second);
			dq.pop_front();
		}
		cnt=0;
		while(dq.size()>1){
			if(sente.count(dq.back().first)){
				dq.pop_back();
				continue;
			}
			if(cnt==1)break;
			cnt++;
			sente.insert(dq.back().second);
			dq.pop_back();
		}
	}
	ll goteans=dq[0].first;

	if(senteans==goteans){
		ans.push_back(goteans);
	}else{
		ans.push_back(senteans);
		ans.push_back(goteans);
	}

	mp[node]=ans;
	return ans;
}

int main(){
    ll n;
	cin>>n;
	g=vvl(n);
	loop(i,1,n-1){
		ll a;
		cin>>a;
		a--;
		g[a].push_back(i);
	}
	cost=vl(n,-1);
	rep(i,n){
		if(g[i].size()==0)cost[i]=i+1;
	}

	rrep(i,n)dfs(i);

	vl ans=dfs(0);

	cout<<ans[0]<<endl;
}