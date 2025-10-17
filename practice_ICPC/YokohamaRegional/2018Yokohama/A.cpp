#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; i++)

int main(){
    ll n;
    cin >> n;
    vector<vector<pair<ll, bool>>> names;
    rep(i, n + 1){
        string s;
        cin >> s;
        vector<pair<ll, bool>> name;
        rep(j, s.size()){
            if('0' <= s[j] && s[j] <= '9'){
                if(name.size() != 0){
                    if(name[name.size() - 1].second){
                        name[name.size() - 1].first *= 10;
                        name[name.size() - 1].first += s[j] - '0';
                    }else{
                        name.push_back({s[j] - '0', true});
                    }
                }else{
                    name.push_back({s[j] - '0', true});
                }
            }else{
                name.push_back({s[j], false});
            }
        }
        names.push_back(name);
    }
    for(ll i = 1; i < n + 1; i++){
        bool f = false;
        for(ll j = 0; j < min(names[0].size(), names[i].size()); j++){
            if(names[0][j].second && !names[i][j].second){
                cout << "+\n";
                f = true;
                break;
            }
            if(!names[0][j].second && names[i][j].second){
                cout << "-\n";
                f = true;
                break;
            }
            else if(names[0][j].first > names[i][j].first){
                cout << "-\n";
                f = true;
                break;
            }else if(names[0][j].first < names[i][j].first){
                cout << "+\n";
                f = true;
                break;
            }
        }
        if(!f){
            if(names[0].size() <= names[i].size()){
                cout << "+\n";
            }
            else{
                cout << "-\n";
            }
        }
    }
}