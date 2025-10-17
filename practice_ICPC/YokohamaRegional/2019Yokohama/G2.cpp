#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define INF 1LL << 60
int main(){
    ll n;
    cin >> n;
    vector<string> s(n);
    set<string> input;
    rep(i, n){
        cin >> s[i];
        input.insert(s[i]);
    }
    map<string, vector<string>> G;
    // s[i]とs[j]の接頭辞が同じなら、辺を貼る
    rep(i, n){
        for(ll j = 1; j < s[i].size(); j++){
            string temp1 = s[i].substr(0, j);
            string temp2 = s[i].substr(j);
            G[temp1].push_back(temp2);
			
        }
    }
    priority_queue<pair<ll, string>, vector<pair<ll, string>>, greater<pair<ll, string>>> pq;
    map<string, ll> cost;
    rep(i, n){
        pq.push({s[i].size(), s[i]});
        cost[s[i]] = s[i].size();
    }

    for(auto p : G){
        //cout << p.first << ":";
        rep(i, p.second.size()){
            //cout << p.second[i] << " ";
        }
        //cout << "\n";
    }

    ll ans = INF;
    while(!pq.empty()){
        auto p = pq.top();
        ll nowcost = p.first;
        string nownode = p.second;
        pq.pop();

        if(nowcost > cost[nownode])continue;

        string settouji = "";
        rep(i, nownode.size()){
            
            if(input.count(settouji)){
                string usiro = nownode.substr(i);
                if(!cost.count(usiro)){
                    // マップにない時は遷移
                    // コスト0の遷移
                    pq.push({nowcost, usiro});
                    cost[usiro] = nowcost;
                }else{
                    // マップにあった場合
                    if(input.count(usiro)){
                        // 答えの更新
                        ans = min(nowcost, ans);
						//if(nowcost==2)cout<<"cost2 "<<settouji<<endl;
                    }else{
                        if(nowcost < cost[usiro]){
                            pq.push({nowcost, usiro});
                            cost[usiro] = nowcost;
                        }
                    }
                }
            }
			settouji.push_back(nownode[i]);
        }

        for(string nextnode : G[nownode]){

            if(cost.count(nextnode)){
                //あった場合 文字を消しきれる
                if(input.count(nextnode)){
                    ans = min(cost[nownode] + (ll)nextnode.size(), ans);
                }else{
                    ll nextcost = cost[nownode] + (ll)nextnode.size();
                    if(nextcost < cost[nextnode]){
                        pq.push({nextcost, nextnode});
                        cost[nextnode] = nextcost;
                    }
                }

            }else{
                ll nextcost = cost[nownode] + (ll)nextnode.size();
                pq.push({nextcost, nextnode});
                cost[nextnode] = nextcost;
            }
        }
    }

    if(ans == INF)cout << "0\n";
    else cout << ans << '\n';

	
}