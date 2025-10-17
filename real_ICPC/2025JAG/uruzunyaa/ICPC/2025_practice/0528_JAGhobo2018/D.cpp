#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

ll return_hash(const string& s, const string& p){
    stack<char> op;
    stack<ll> num;
    rep(i, s.length()){
        if(s[i] == 'a')num.push(p[0] - '0');
        else if(s[i] == 'b')num.push(p[1] - '0');
        else if(s[i] == 'c')num.push(p[2] - '0');
        else if(s[i] == 'd')num.push(p[3] - '0');
        else op.push(s[i]);
        if(!op.empty() && op.top() == ']'){
            ll num2 = num.top();
            num.pop();
            ll num1 = num.top();
            num.pop();
            op.pop();
            char ope = op.top();
            op.pop();
            op.pop();
            if(ope == '+')num.push(num1 | num2);
            else if(ope == '*')num.push(num1 & num2);
            else if(ope == '^')num.push(num1 ^ num2);
        }
    }
    return num.top();
}

int main() {
    while(1){
        string s,p;
        cin >> s >> p;
        if(s == ".")break;
        ll hash = return_hash(s,p);
        ll ans = 0;
        for(ll i = 0; i <= 9999; i++){
            string pass = to_string(i);
            while(pass.length() < 4){
                pass.insert(0,"0");
            }
            if(hash == return_hash(s,pass))ans++;
        }
        cout << hash << " " << ans << endl;
    }
    return 0;
}