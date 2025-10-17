#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

int solve() {
    string s;
    cin >> s;
	if(s == "#"){return 1;}
    ll a,b,c,d;
    cin >> a >> b >> c >> d;

    ll slash_cnt = 0;
    rep(i, s.length()){
        if(s[i] == '/'){
            slash_cnt++;
        }
    }
    vector<vector<ll>> board(slash_cnt + 1);
    ll j = 0;
    rep(i, s.length()){
        if(s[i] >= '0' && s[i] <= '9'){
            rep(k, (s[i] - '0')){
                board[j].push_back('.');
            }
        }else if(s[i] == '/'){
            j++;
        } else {
            board[j].push_back('b');
        }
    }
    board[--a][--b] = '.';
    board[--c][--d] = 'b';
    queue<pair<char,ll>> q;
    rep(i, board.size()){
        rep(j, board[i].size()){
            if(board[i][j] == '.'){
                if(!q.empty() && q.back().first == 'n'){
                    q.back().second++;
                }else{
                    q.push({'n',1});
                }
            }
            if(board[i][j] == 'b'){
                q.push({'b',1});
            }
        }
        if(i != board.size() - 1)q.push({'/',1});
    }
    while(!q.empty()){
        if(q.front().first == 'n'){
            cout << q.front().second;
        }else{
            cout << q.front().first;
        }
        q.pop();
    }
    cout << endl;
    return 0;
}
int main() {
    while(solve() == 0);
    return 0;
}