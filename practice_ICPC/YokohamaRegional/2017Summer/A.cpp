#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main(){
    string s;
    cin >> s;
    stack<char> st;
    rep(i, s.length()){
        if(st.empty()){
            st.push(s[i]);
        }else if(s[i] == ')' && st.top() == '('){
            st.pop();
        }else{
            st.push(s[i]);
        }
    }
    ll ans = 0;
    while(!st.empty()){
        if(st.top() == '('){
            ans++;
        }
        st.pop();
    }
    cout << ans << endl;
}