#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    string s; cin >> s;
    unordered_set<char> n;
    for (auto c : s) {
        if ('a' <= c && c <= 'z') n.insert(c);
    }

    unordered_map<char, ll> forms;
    rep(i, n.size()) {
        char a;
        ll v;
        cin >> a >> v;
        forms[a] = v;
    }


    auto dfs = [&](auto dfs, int& i) -> ll {
        vector<ll> ret;

        if (s[i] == '[') {
            i++;
            ret.push_back(dfs(dfs, i));
        }
        else {
            assert('a' <= s[i] && s[i] <= 'z');
            ret.push_back(forms[s[i]]);
        }

        i++;

        if (s[i] == ']' || i >= s.size()) {
            assert(ret.size() == 1);
            return ret[0] - 1;
        }

        assert(s[i] == '-');
        i++;

        if (s[i] == '[') {
            i++;
            ret.push_back(dfs(dfs, i));
        }
        else {
            assert('a' <= s[i] && s[i] <= 'z');
            ret.push_back(forms[s[i]]);
        }

        i++;

        assert(ret.size() == 2);
        if (ret[0] < 0 || ret[1] < 0) {
            return -1001001001;
        }
        if (ret[0] != 0 && ret[1] != 0) {
            return -1001001001;
        }
        if (ret[0] == 0 && ret[1] == 0) {
            return -1001001001;
        }
        return max(ret[0], ret[1]) - 1;
    };
    int i = 0;
    ll ret = dfs(dfs, i);

    if (ret == -1) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}