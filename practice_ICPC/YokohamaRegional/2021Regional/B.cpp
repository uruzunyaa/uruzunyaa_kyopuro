#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
const ll INF = 1LL << 60;

int main(){
    ll n;
    cin >> n;
    vector<string> s(n);
    unordered_map<string, ll> two_cnt, four_cnt;
    rep(i, n){
        cin >> s[i];
        string last_two = s[i].substr(4, 2);
        string last_four = s[i].substr(2, 4);
        two_cnt[last_two]++;
        four_cnt[last_four]++;
    }

    vector<pair<ll, string>> count;
    for(auto [last_two, cnt] : two_cnt){
        count.push_back({cnt, last_two});
    }
    sort(count.rbegin(), count.rend());

    vector<pair<ll, string>> top5;
    rep(i, min((int)count.size(), 5)){
        top5.push_back(count[i]);
    }
    while(top5.size() <= 5){
        top5.push_back({0, "-1"});
    }

    vector<pair<ll, string>> count2;
    for(auto [last_four, cnt] : four_cnt){
        string last_two = last_four.substr(2, 2);
        count2.push_back({cnt, last_two});
    }
    sort(count2.rbegin(), count2.rend());

    vector<ll> distribution = {1, 2, 3, 3, 3};
    ll ans = 0;
    do{
        ll temp = 0;
        set<string> se;
        rep(i, 5){
            if(distribution[i] == 1 || distribution[i] == 3)se.insert(top5[i].second);
        }

        rep(i, 5){
            if(distribution[i] == 1){
                if(top5[i].first != 0 && top5[i].second != "-1")temp += 300000;
            }else if(distribution[i] == 2){
                if(top5[i].first == 0)continue;
                if(top5[i].first != 0 && top5[i].second != "-1"){
                    rep(j, count2.size()){
                        if(!se.count(count2[j].second)){
                            temp += 4000 * count2[j].first;
                            break;
                        }
                    }

                }
            }else if(distribution[i] == 3){
                if(top5[i].first == 0 || top5[i].second == "-1")continue;
                temp += 500 * top5[i].first;
            }
        }
        ans = max(ans, temp);

    }while(next_permutation(distribution.begin(), distribution.end()));

    cout << ans << endl;
}