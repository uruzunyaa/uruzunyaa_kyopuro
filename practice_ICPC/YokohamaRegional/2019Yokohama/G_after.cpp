#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i,m, n) for(ll i = m; i <= n; ++i)
#define inf 1LL << 60

//グラフgの頂点startからの最短経路を全ての頂点に対して求める。
vl dijkstra(vector<vector<pair<ll,ll>>> g,ll start){
	priority_queue<pair<ll,ll>> dj;
	vl cost(g.size(),inf);
	cost[start]=0;
	dj.push({start,0});
	while(!dj.empty()){
		ll nowcost=-dj.top().first;
		ll tmp=dj.top().second;
		dj.pop();
		if(cost[tmp]<nowcost)continue;
		rep(i,g[tmp].size()){
			if(cost[g[tmp][i].first]>nowcost+g[tmp][i].second){
				cost[g[tmp][i].first]=nowcost+g[tmp][i].second;
				dj.push({-cost[g[tmp][i].first],g[tmp][i].first});
			}
		}
	}
	return cost;
}

//どちらかがどちらかの接頭辞になっていなければ、"error"を返す
//なっていれば、マッチしなかった残りの文字を返す
//マッチ後の文字列がinputに含まれてたらgoalを返す
set<string> input;

string matching (string s,string t){
	if(s.size()>t.size())swap(s,t);
	bool f=true;
	rep(i,s.size()){
		if(s[i]!=t[i]){
			f=false;
			break;
		}
	}
	if(f){
		string ans=t.substr(s.size());
		if(input.count(ans))return "goal";
		else return ans;
	}else{
		 return "error";
	}
}

int main(){
    ll n;
    cin >> n;
    vector<string> s(n);
    
	//グラフの頂点と番号の対応を作る(全ての入力の部分文字列に対して)
	ll mpcnt=0;
	map<string,ll> mp;
	mp["start"]=mpcnt;
	mpcnt++;
    rep(i, n){
        cin >> s[i];
        input.insert(s[i]);

		//部分文字列しか頂点に成り得ない/部分文字列は少ない
		rep(j,s[i].size()){
			rep(k,j+1){
				string tmp;
				loop(l,k,j)tmp.push_back(s[i][l]);
				if(!mp.count(tmp)){
					
					mp[tmp]=mpcnt;
					mpcnt++;
				}
			}
		}
    }


	mp["goal"]= mpcnt;
	mpcnt++;

	//グラフを実際に構築(全ての頂点に対して入力文字のmatchingを考える)
	vector<vector<pair<ll,ll>>> g(mpcnt);
	for(const auto & val:mp){
		rep(i,n){
			if(val.first==s[i])continue;
			string tmp=matching(val.first,s[i]);
			if(tmp=="error")continue;
			
			ll cost;
			if(val.first.size()<s[i].size()){
				if(tmp=="goal")cost=s[i].size()-val.first.size();
				else cost=tmp.size();
			}else{
				cost=0;
			}

			g[val.second].push_back({mp[tmp],cost});
		}
	}

	rep(i,n){
		g[0].push_back({mp[s[i]],s[i].size()});
	}

	//作り終わったグラフにダイクストラ関数を呼んで適応。
	vl ans = dijkstra(g,0);
	if(ans.back()!=inf)cout<<ans.back()<<endl;
	else cout<<0<<endl;
}